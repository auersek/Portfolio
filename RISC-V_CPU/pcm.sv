module pcm #(
    parameter DATA_WIDTH = 32
)(
    input logic                       clk,      
    // control cascade
    input logic                       regWrite_m,
    input logic [1:0]                 resultSrc_m,

    // data
    input logic [DATA_WIDTH-1:0]      aluResult_m,
    input logic [DATA_WIDTH-1:0]      readData_m,
    input logic [4:0]                 destinationReg_m,
    input logic [DATA_WIDTH-1:0]      pcPlus4_m,

    // outputs control cascade
    output logic                       regWrite_w,
    output logic [1:0]                 resultSrc_w,

    // outputs data
    output logic [DATA_WIDTH-1:0]      aluResult_w,
    output logic [DATA_WIDTH-1:0]      readData_w,
    output logic [4:0]                 destinationReg_w,
    output logic [DATA_WIDTH-1:0]      pcPlus4_w
);

always_ff @(posedge clk) begin
    regWrite_w      <= regWrite_m;
    resultSrc_w     <= resultSrc_m;

    aluResult_w     <= aluResult_m;
    readData_w      <= readData_m;
    destinationReg_w <= destinationReg_m;
    pcPlus4_w       <= pcPlus4_m;
end

endmodule
