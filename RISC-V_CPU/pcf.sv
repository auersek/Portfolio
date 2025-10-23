module pcf #(
    parameter DATA_WIDTH = 32
)(
    input logic                       clk,
    input logic                       stall,   
    input logic                       flush,    
    // Input data
    input logic [DATA_WIDTH-1:0]      instruction,
    input logic [DATA_WIDTH-1:0]      pc_f,
    input logic [DATA_WIDTH-1:0]      pcPlus4_f,
    // Output data
    output logic [DATA_WIDTH-1:0]     instruction_out,
    output logic [DATA_WIDTH-1:0]     pc_d,
    output logic [DATA_WIDTH-1:0]     pcPlus4_d
);

always_ff @(posedge clk) begin
    if (flush) begin
        instruction_out <= 0;
        pc_d <= 0;
        pcPlus4_d <= 0;
    end else if (!stall) begin
        instruction_out <= instruction;
        pc_d <= pc_f;
        pcPlus4_d <= pcPlus4_f;
    end
end

endmodule
