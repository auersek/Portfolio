#include "verilated.h"
#include "verilated_vcd_c.h"
#include "VL1Cache.h"
#include "gtest/gtest.h"
#include <memory>
#include <queue>
#include <random>

class L1CacheTest : public ::testing::Test {
protected:
    std::unique_ptr<VerilatedContext> contextp;
    std::unique_ptr<VL1Cache> dut;
    std::unique_ptr<VerilatedVcdC> trace;
    vluint64_t main_time;
    std::queue<uint32_t> mem_response_queue;
    std::mt19937 rng;

    void SetUp() override {
        contextp = std::make_unique<VerilatedContext>();
        contextp->debug(0);
        contextp->randReset(2);
        contextp->traceEverOn(true);
        dut = std::make_unique<VL1Cache>(contextp.get());
        if (trace_enabled()) {
            trace = std::make_unique<VerilatedVcdC>();
            if (trace) {
                dut->trace(trace.get(), 99);
                trace->open("L1Cache.vcd");
            }
        }
        main_time = 0;
        rng.seed(std::random_device()());
        dut->clk = 0;
        dut->rst_n = 0;
        dut->load = 0;
        dut->store = 0;
        dut->address = 0;
        dut->data_in = 0;
        dut->mem_data = 0;
        dut->mem_ready = 0;
        dut->eval();
        for (int i = 0; i < 5; i++) cycle();
        dut->rst_n = 1;
        cycle();
    }

    void TearDown() override {
        if (trace) {
            trace->close();
            trace.reset();
        }
        dut.reset();
        contextp.reset();
    }

    bool trace_enabled() const { return true; }

    void tick() {
        contextp->timeInc(1);
        dut->clk = !dut->clk;
        dut->eval();
        if (trace) {
            trace->dump(contextp->time());
        }
        if (dut->mem_read || dut->mem_write) {
            handle_memory_operation();
        }
    }

    void cycle() {
        tick();
        tick();
        dut->eval();
    }

    void handle_memory_operation() {
        static int delay_counter = 0;
        if (delay_counter >= 4) {
            dut->mem_ready = 1;
            if (!mem_response_queue.empty()) {
                dut->mem_data = mem_response_queue.front();
                mem_response_queue.pop();
            }
            delay_counter = 0;
        } else {
            dut->mem_ready = 0;
            delay_counter++;
        }
        dut->eval();
    }

    void queue_memory_response(uint32_t data) {
        mem_response_queue.push(data);
    }

    uint32_t random_address() {
        return (rng() & 0xFFFFFFFC);
    }

    uint32_t random_data() {
        return rng();
    }

    void wait_until_not_busy(int max_cycles = 100) {
        int cycles = 0;
        while (dut->busy && cycles < max_cycles) {
            cycle();
            cycles++;
        }
        ASSERT_LT(cycles, max_cycles) << "Cache busy timeout";
    }
};

TEST_F(L1CacheTest, BasicWriteRead) {
    uint32_t test_addr = 0x1000;
    uint32_t test_data = 0xDEADBEEF;

    dut->store = 1;
    dut->address = test_addr;
    dut->data_in = test_data;
    dut->eval();
    cycle();
    wait_until_not_busy();
    dut->store = 0;
    dut->eval();
    cycle();

    dut->load = 1;
    dut->address = test_addr;
    dut->eval();
    cycle();
    EXPECT_EQ(dut->hit, 1);
    if (dut->hit) {
        EXPECT_EQ(dut->data_out, test_data);
    }
    wait_until_not_busy();
    dut->load = 0;
    dut->eval();
    cycle();
}

TEST_F(L1CacheTest, CacheMiss) {
    uint32_t test_addr = 0x2000;
    uint32_t test_data = 0x12345678;
    queue_memory_response(test_data);
    dut->load = 1;
    dut->address = test_addr;
    dut->eval();
    cycle();
    EXPECT_EQ(dut->hit, 0);
    EXPECT_EQ(dut->miss, 1);
    wait_until_not_busy();
    EXPECT_EQ(dut->data_out, test_data);
    dut->load = 0;
    dut->eval();
    cycle();
}

TEST_F(L1CacheTest, CacheReplacement) {
    const int WAYS = 2;
    const uint32_t BASE_ADDR = 0x3000;
    std::vector<uint32_t> test_data;
    
    for (int i = 0; i < WAYS + 1; i++) {
        test_data.push_back(random_data());
        queue_memory_response(test_data.back());
    }

    // Fill cache ways
    for (int i = 0; i < WAYS + 1; i++) {
        dut->store = 1;
        dut->address = BASE_ADDR + (i * 0x1000);
        dut->data_in = test_data[i];
        dut->eval();
        cycle();
        wait_until_not_busy();
        dut->store = 0;
        dut->eval();
        cycle();
    }

    dut->load = 1;
    dut->address = BASE_ADDR + (WAYS * 0x1000);
    dut->eval();
    cycle();
    EXPECT_EQ(dut->hit, 1);
    EXPECT_EQ(dut->data_out, test_data[WAYS]);
    wait_until_not_busy();
    dut->load = 0;
    dut->eval();
    cycle();
}

TEST_F(L1CacheTest, WriteBack) {
    // Fill cache with data that maps to the same cache set,
    const int NUM_WRITES = 3; // Should be more than cache ways?
    const uint32_t BASE_ADDR = 0x2000;
    const uint32_t SET_OFFSET = 0x10000; // Ensure addresses map to same set
    std::vector<uint32_t> test_data;
    
    // queuing for memory responses
    for (int i = 0; i < NUM_WRITES; i++) {
        test_data.push_back(0xDEAD0000 + i);
        queue_memory_response(test_data.back());
    }

    // Fill cache and make lines dirty
    for (int i = 0; i < NUM_WRITES; i++) {
        dut->store = 1;
        dut->address = BASE_ADDR + (i * SET_OFFSET);
        dut->data_in = test_data[i];
        dut->eval();
        cycle();
        wait_until_not_busy();
        dut->store = 0;
        dut->eval();
        cycle();

        // this time, the program read it back to verify storage
        dut->load = 1;
        dut->address = BASE_ADDR + (i * SET_OFFSET);
        dut->eval();
        cycle();
        EXPECT_EQ(dut->hit, 1);
        EXPECT_EQ(dut->data_out, test_data[i]);
        wait_until_not_busy();
        dut->load = 0;
        dut->eval();
        cycle();

        dut->store = 1;
        dut->address = BASE_ADDR + (i * SET_OFFSET);
        dut->data_in = test_data[i] ^ 0xFFFFFFFF;  // Modified data which is dirty for testing purpos
        dut->eval();
        cycle();
        wait_until_not_busy();
        dut->store = 0;
        dut->eval();
        cycle();
    }

    dut->store = 1;
    dut->address = BASE_ADDR + (NUM_WRITES * SET_OFFSET);
    dut->data_in = 0xDEADBEEF;
    dut->eval();
    cycle();

    bool write_back_triggered = false;
    for (int i = 0; i < 10; i++) {
        if (dut->mem_write) {
            write_back_triggered = true;
            break;
        }
        cycle();
    }
    EXPECT_TRUE(write_back_triggered) << "Write-back was not triggered";
    
    wait_until_not_busy();
    dut->store = 0;
    dut->eval();
    cycle();
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}