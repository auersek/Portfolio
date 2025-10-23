module pcd #(
    parameter DATA_WIDTH = 32
)(
    input logic                       clk,
    // input logic                       stall,           
    input logic                       flush,     

    // control cascade
    input logic                       regWrite_d,
    input logic [1:0]                 resultSrc_d,
    input logic                       memWrite_d,
    input logic [4:0]                 aluControl_d,
    input logic                       aluSrc_d,
    input logic [2:0]                 MemCtrl_d, 
    input logic                       branch_d,
    input logic                       jalr_d,               // ADD TO THE OTHER PCD
    input logic                       jump_d,
    input logic                       memRead_d,
    input logic                       MemStore_d,
    // input logic [2:0]                 PCSrc_d,

    // data
    input logic [DATA_WIDTH-1:0]      rd1_d,
    input logic [DATA_WIDTH-1:0]      rd2_d,
    input logic [DATA_WIDTH-1:0]      pc_d,
    input logic [4:0]                 destinationReg_d,
    input logic [4:0]                 rs1_d,
    input logic [4:0]                 rs2_d,
    input logic [DATA_WIDTH-1:0]      immExt_d,
    input logic [DATA_WIDTH-1:0]      pcPlus4_d,

    // outputs control cascade
    output logic                       regWrite_e,
    output logic [1:0]                 resultSrc_e,
    output logic                       memWrite_e,
    output logic [4:0]                 aluControl_e,
    output logic                       aluSrc_e,
    output logic [2:0]                 MemCtrl_e, 
    output logic                       branch_e,
    output logic                       jalr_e,  
    output logic                       jump_e,
    output logic                       memRead_e,
    output logic                       MemStore_e,
    // output logic [2:0]                 PCSrc_e,

    // outputs data
    output logic [DATA_WIDTH-1:0]      rd1_e,
    output logic [DATA_WIDTH-1:0]      rd2_e,
    output logic [DATA_WIDTH-1:0]      pc_e,
    output logic [4:0]                 destinationReg_e,
    output logic [4:0]                 rs1_e,
    output logic [4:0]                 rs2_e,
    output logic [DATA_WIDTH-1:0]      immExt_e,
    output logic [DATA_WIDTH-1:0]      pcPlus4_e
);


always_ff @(posedge clk) begin
    if (flush) begin
        regWrite_e      <= 0;
        resultSrc_e     <= 2'b00;
        memWrite_e      <= 0;
        MemCtrl_e       <= 3'b000;
        // PCSrc_e         <= 3'b000;
        branch_e        <= 0;
        jalr_e          <= 0;
        jump_e          <= 0;
        memRead_e       <= 0;
        MemStore_e      <= 0;

        aluControl_e    <= 5'b00000;
        aluSrc_e        <= 0;

        rd1_e           <= 0;
        rd2_e           <= 0;
        pc_e            <= 0;
        destinationReg_e <= 0;
        rs1_e           <= 0;
        rs2_e           <= 0;
        immExt_e        <= 0;
        pcPlus4_e       <= 0;
    // end else if (stall) begin
    //     regWrite_e      <= regWrite_e;
    //     resultSrc_e     <= resultSrc_e;
    //     memWrite_e      <= memWrite_e;
    //     MemCtrl_e       <= MemCtrl_e;
    //     // PCSrc_e         <= PCSrc_e;
    //     branch_e        <= branch_e;
    //     jump_e          <= jump_e;
    //     aluControl_e    <= aluControl_e;
    //     aluSrc_e        <= aluSrc_e;
    //     memRead_e       <= memRead_e;

    //     rd1_e           <= rd1_e;
    //     rd2_e           <= rd2_e;
    //     pc_e            <= pc_e;
    //     destinationReg_e <= destinationReg_e;
    //     rs1_e           <= rs1_e;
    //     rs2_e           <= rs2_e;
    //     immExt_e        <= immExt_e;
    //     pcPlus4_e       <= pcPlus4_e;
    end else begin
        regWrite_e      <= regWrite_d;
        resultSrc_e     <= resultSrc_d;
        memWrite_e      <= memWrite_d;
        MemCtrl_e       <= MemCtrl_d;
        branch_e        <= branch_d;
        jump_e          <= jump_d;
        jalr_e          <= jalr_d;
        aluControl_e    <= aluControl_d;
        aluSrc_e        <= aluSrc_d;
        memRead_e       <= memRead_d;
        MemStore_e      <= MemStore_d;

        rd1_e           <= rd1_d;
        rd2_e           <= rd2_d;
        pc_e            <= pc_d;
        destinationReg_e <= destinationReg_d;
        rs1_e           <= rs1_d;
        rs2_e           <= rs2_d;
        immExt_e        <= immExt_d;
        pcPlus4_e       <= pcPlus4_d;
    end
end

// endmodule





endmodule
