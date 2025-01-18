module cacheFSM #(
    parameter ADDR_WIDTH = 32,
    parameter DATA_WIDTH = 32
) (
    input  logic clk,
    input  logic write_en,
    input  logic read_en,
    input  logic [2:0] addr_mode,
    input  logic [ADDR_WIDTH-1:0] addr,
    input  logic [DATA_WIDTH-1:0] write_data,
    output logic [DATA_WIDTH-1:0] out
);

// Cache line structure
typedef struct packed {
    logic valid;
    logic dirty;
    logic [27:0] tag;
    logic [DATA_WIDTH-1:0] data;
    logic lru;
} cache_line;

// Two-way set associative cache
cache_line cache [2][4];

// FSM state enumeration
typedef enum logic [1:0] { Idle, Compare, Allocate, WriteBack } fsm_state_t;

fsm_state_t current_state, next_state;

// Internal signals
logic [DATA_WIDTH-1:0] read_data;
logic [27:0] tag;
logic [1:0] set;
logic fetch_in_progress;
logic write_back_in_progress;
logic memory_ready;
logic hit;
logic [ADDR_WIDTH-1:0] evicted_addr;
logic lru_select; // Used to determine selected way during Compare

// Extract tag and set from address
always_comb begin
    tag = addr[31:4];
    set = addr[3:2];
    hit = 0;
    out = 0;

    // Check for cache hit
    if (cache[0][set].valid && cache[0][set].tag == tag) begin
        hit = 1;
        out = cache[0][set].data;
    end else if (cache[1][set].valid && cache[1][set].tag == tag) begin
        hit = 1;
        out = cache[1][set].data;
    end else begin
        hit = 0;
        out = read_data;
    end

    // Determine LRU way (only for misses)
    lru_select = cache[0][set].lru ? 1 : 0;
end

// FSM behavior
always_ff @(posedge clk) begin
    current_state <= next_state;

    case (current_state)
        Idle: begin
            if (read_en || write_en) begin
                next_state <= Compare;
            end else begin
                next_state <= Idle;
            end
        end

        Compare: begin
            if (hit) begin
                if (write_en) begin
                    logic way = cache[0][set].valid && cache[0][set].tag == tag ? 0 : 1;
                    cache[way][set].data <= write_data;
                    cache[way][set].dirty <= 1;
                    cache[way][set].lru <= 0;
                    cache[~way][set].lru <= 1;
                    next_state <= Idle;
                end else begin
                    next_state <= Idle;
                end
            end else begin
                if (cache[lru_select][set].dirty) begin
                    write_back_in_progress <= 1;
                    evicted_addr <= {cache[lru_select][set].tag, set, 2'b00};
                    next_state <= WriteBack;
                end else begin
                    fetch_in_progress <= 1;
                    next_state <= Allocate;
                end
            end
        end

        Allocate: begin
            if (memory_ready) begin
                cache[lru_select][set].valid <= 1;
                cache[lru_select][set].tag <= tag;
                cache[lru_select][set].data <= read_data;
                cache[lru_select][set].dirty <= 0;
                cache[lru_select][set].lru <= 0;
                cache[~lru_select][set].lru <= 1;
                fetch_in_progress <= 0;
                next_state <= Compare;
            end else begin
                next_state <= Allocate;
            end
        end

        WriteBack: begin
            if (memory_ready) begin
                write_back_in_progress <= 0;
                fetch_in_progress <= 1;
                next_state <= Allocate;
            end else begin
                next_state <= WriteBack;
            end
        end

        default: begin
            next_state <= Idle;
        end
    endcase
end

// Memory interface

dataMemCached dataMemory (
    .clk(clk),
    .memCtrl(addr_mode),
    .Address(write_back_in_progress ? evicted_addr : addr),
    .WriteData(write_back_in_progress ? cache[lru_select][set].data : write_data),
    .memWriteAllowed(write_en),            // write_back_in_progress || (           // && !hit)
    .memReadAllowed(read_en),     //fetch_in_progress || //   && !hit)
    .ReadData(read_data),
    .ready(memory_ready)
);

endmodule
