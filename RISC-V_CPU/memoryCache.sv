module memoryCache #(
    parameter WD = 32 // WordData width
)(
    input  logic              hit,          // Hit signal
    input  logic [WD-1:0]     Cachein,      // Cache output data
    input  logic [WD-1:0]     Memoryin,     // Memory data input
    output logic [WD-1:0]     Cacheout      // Cache output data
);
    
    always_comb begin
        if (hit) begin
            Cacheout = Cachein;
        end else begin
            Cacheout = Memoryin;
        end
    end

endmodule
