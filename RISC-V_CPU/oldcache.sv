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
    output logic cacheStall,
    output logic [DATA_WIDTH-1:0] out
);

typedef struct packed {
    logic valid;            
    logic dirty;
    logic [27:0] tag;
    logic [31:0] data;
    logic lru;
} cache_line;

cache_line cache [2][4];

typedef enum logic [1:0] { Idle, Compare, Allocate, WriteBack } fsm_state_t;
fsm_state_t current_state, next_state;

logic [DATA_WIDTH-1:0] read_data;       
logic [27:0] tag;                      
logic [1:0] set;                       
logic way_select;                      
logic fetch_in_progress;              
logic write_back_in_progress;           
logic memory_ready;                    
logic hit;                             
logic [ADDR_WIDTH-1:0] evicted_addr;   

always_comb begin
    tag = addr[31:4];
    set = addr[3:2];
    hit = 0;
    way_select = 0;
    out = 0;

    if (cache[0][set].valid && cache[0][set].tag == tag) begin
        hit = 1;
        way_select = 0;
        out = cache[0][set].data;
    end else if (cache[1][set].valid && cache[1][set].tag == tag) begin
        hit = 1;
        way_select = 1;
        out = cache[1][set].data;
    end
    else begin 
        hit = 0;
        out = read_data;
    end
end

assign cacheStall = 0;

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
                    cache[way_select][set].data <= write_data;
                    cache[way_select][set].dirty <= 1;
                    cache[way_select][set].lru <= 0;
                    cache[~way_select][set].lru <= 1; 
                    next_state <= Idle;
                end
            end else if (!hit && cache[way_select][set].dirty) begin
                next_state <= WriteBack;
                write_back_in_progress <= 1;
                evicted_addr <= {cache[way_select][set].tag, set, 2'b00};
            end else begin
                next_state <= Allocate;
                fetch_in_progress <= 1;
            end
        end

        Allocate: begin
            if (memory_ready) begin
                cache[way_select][set].valid <= 1;
                cache[way_select][set].tag <= tag;
                cache[way_select][set].data <= read_data;
                cache[way_select][set].dirty <= 0;
                fetch_in_progress <= 0;
                next_state <= Compare;
            end
            else begin 
                next_state <= current_state;
            end
        end

        WriteBack: begin
            if (memory_ready) begin
                write_back_in_progress <= 0;
                fetch_in_progress <= 1; 
                next_state <= Allocate;
            end
            else begin 
                next_state <= current_state;
            end
        end

        default: begin
            next_state <= Idle; 
        end
    endcase
    // CacheStall = fetch_in_progress || write_back_in_progress || (we && !hit);
end

dataMemCached dataMemory (
    .clk(clk),
    .memCtrl(addr_mode),
    .Address(write_back_in_progress ? evicted_addr : addr),
    .WriteData(write_back_in_progress ? cache[way_select][set].data : write_data),
    .memWriteAllowed(write_back_in_progress || (write_en && !hit)),   //  
    .memReadAllowed(fetch_in_progress || read_en),         //  && !hit)
    .ReadData(read_data),
    .ready(memory_ready)
);

endmodule
