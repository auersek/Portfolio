module cacheFSM #(
  parameter TAGSIZE = 32 - $clog2(SETNUM), // Tag size derived from address size and number of sets
  parameter SETNUM = 8,                   // Number of sets
  parameter DEGREE = 2                    // Associativity (number of ways)
)(
  input logic [31:0] addressIn,           // Input address
  input logic [31:0] dataIn,              // Input data
 
  input logic LoadMemory,                      // Load type signal
  input logic storeMemory,

  input logic memwriteM,                  // Write enable signal
  input logic clk,                        // Clock signal
  input logic [31:0] memIn,               // Data input from memory
  output logic [31:0] Dataout,            // Cache output data
  output logic hit                        // Hit signal (1 if cache hit, 0 otherwise)
//   output logic stall                   // Stall signal (1 if cache is busy, 0 otherwise)
);

  // Cache structures
  logic [SETNUM-1:0][DEGREE-1:0] valid;                      // Valid bits for each cache line
  logic [SETNUM-1:0][DEGREE-1:0][TAGSIZE-1:0] tag;           // Tag bits for each cache line
  logic [SETNUM-1:0][DEGREE-1:0][31:0] data;                 // Data storage for each cache line (block size: 32 bits)
  logic [SETNUM-1:0] lru;                                   // LRU bit for each set (0: way 0, 1: way 1)
  logic [DEGREE-1:0] way_sel;                               // Selected way for replacement

  // Address breakdown
  logic [TAGSIZE-1:0] Tag_in;                             // Extracted tag from input address
  logic [$clog2(SETNUM)-1:0] set_index;                     // Extracted set index from input address

  assign Tag_in = addressIn[31:3];                        // Tag bits from the address (ignoring byte offset)
  assign set_index = addressIn[2:0];                        // Set index (bits 2:0 from address)

  
  // Initialization
  initial begin
    for (int set = 0; set < SETNUM; set++) begin
      lru[set] = 0;                                         // Initialize LRU bits to 0
      for (int way = 0; way < DEGREE; way++) begin
        valid[set][way] = 1'b0;                            // Mark all cache lines as invalid initially
      end
    end
  end

  // Cache Read Logic
  always_comb begin
    hit = 1'b0;                                            // Default: miss
    Dataout = 32'b0;                                       // Default: no data
    
    if (LoadMemory) begin                                       // If load operation
      for (int way = 0; way < DEGREE; way++) begin
        if (valid[set_index][way] && tag[set_index][way] == Tag_in) begin
          Dataout = {{24{1'b0}}, data[set_index][way][7:0]}; // Return lower byte of the data (zero-extended)
          hit = 1'b1;                                      // Cache hit
        end
      end
    end
  end

  // Cache Update Logic
  always_ff @(posedge clk) begin
    // On a cache hit during load, update LRU
    if (LoadMemory && hit) begin
      lru[set_index] <= !lru[set_index];                   // Toggle LRU for the set
    end

    // On a cache miss during load, fetch data from memory and update cache
    if (LoadMemory && !hit) begin
      lru[set_index] <= !lru[set_index];                   // Toggle LRU for the set
      way_sel = lru[set_index] ? 1'b0 : 1'b1;              // Select the LRU way for replacement
      valid[set_index][way_sel] <= 1'b1;                   // Mark the line as valid
      tag[set_index][way_sel] <= Tag_in;                 // Update the tag
      data[set_index][way_sel] <= memIn;                   // Load data from memory
    end

    // Handle write operations
    if (memwriteM) begin
      way_sel = lru[set_index] ? 1'b0 : 1'b1;              // Select the LRU way for replacement
      if (storeMemory) begin                                    // Store operation
        valid[set_index][way_sel] <= 1'b1;                 // Mark the line as valid
        tag[set_index][way_sel] <= Tag_in;               // Update the tag
        data[set_index][way_sel][7:0] <= dataIn[7:0];      // Write lower byte of the input data
      end
    end
  end

endmodule
