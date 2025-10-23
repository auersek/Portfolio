module pce #(
    parameter DATA_WIDTH = 32
)(
    input logic                       clk,

    // control cascade
    input logic                       regWrite_e,
    input logic [1:0]                 resultSrc_e,
    input logic                       memWrite_e,
    input logic                       MemRead_e,
    input logic [2:0]                 MemCtrl_e, 
    input logic                       MemStore_e,
    // data
    input logic [DATA_WIDTH-1:0]      aluResult_e,
    input logic [DATA_WIDTH-1:0]      writeData_e,
    input logic [4:0]                 destinationReg_e,
    input logic [DATA_WIDTH-1:0]      pcPlus4_e,

    //outputs control cascade
    output logic                       regWrite_m,
    output logic [1:0]                 resultSrc_m,
    output logic                       memWrite_m,
    output logic                       MemRead_m,
    output logic [2:0]                 MemCtrl_m, 
    output logic                       MemStore_m,
    // outputs data
    output logic [DATA_WIDTH-1:0]      aluResult_m,
    output logic [DATA_WIDTH-1:0]      writeData_m,
    output logic [4:0]                 destinationReg_m,
    output logic [DATA_WIDTH-1:0]      pcPlus4_m
);

always_ff @(posedge clk) begin

    regWrite_m      <= regWrite_e;
    resultSrc_m     <= resultSrc_e;
    memWrite_m      <= memWrite_e;
    MemCtrl_m       <= MemCtrl_e;
    MemRead_m       <= MemRead_e;
    MemStore_m      <= MemStore_e;

    aluResult_m     <= aluResult_e;
    writeData_m     <= writeData_e;
    destinationReg_m <= destinationReg_e;
    pcPlus4_m       <= pcPlus4_e;

end


endmodule
