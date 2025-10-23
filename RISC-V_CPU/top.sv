module top #(
    parameter DATA_WIDTH = 32
)(
    input logic clk,
    input logic rst,
    input logic trigger,
    output logic [DATA_WIDTH-1:0] a0
);

    // Fetch
    logic [DATA_WIDTH-1:0]      pc_F, pc_next_F, pc_Plus4_F, instr_F;
    logic                       stall, flush;
    // Decode 
    logic [DATA_WIDTH-1:0]      instr_D, pc_Plus4_D, pc_D, ImmExt_D, regFileOut1_D, regFileOut2_D;
    logic                       regWrite_D, memWrite_D, ALUsrc_D, jump_D, branch_D, MemRead_D, jalr_D, memStoreD_D, loadD; 
    logic [1:0]                 resultSrc_D;
    logic [2:0]                 immSrc_D, MemCtrl_D; 
    logic [4:0]                 ALUcontrol_D;
    // Execute
    logic [DATA_WIDTH-1:0]      pc_Plus4_E, pc_E, ImmExt_E, regFileOut1_E, regFileOut2_E, ALUout_E, pc_Target_E, ALU_in2_E, mux4SrcA_OUT, mux4SrcB_OUT, jalrMux_out;
    logic [4:0]                 destinationReg_E, rs1_E, rs2_E;
    logic                       regWrite_E, memWrite_E, ALUsrc_E, zero_E, jump_E, branch_E, PCSrc_E, MemRead_E, jalr_E, memStoreD_E;  
    logic [1:0]                 resultSrc_E, forwardA_e, forwardB_e;
    logic [2:0]                 MemCtrl_E;  
    logic [4:0]                 ALUcontrol_E;
    // Memory
    logic [DATA_WIDTH-1:0]      pc_Plus4_M, ALUout_M, WriteData_M, ReadMem_out_M, memoryout, Cacheout;
    logic [4:0]                 destinationReg_M;
    logic                       regWrite_M, memWrite_M, MemRead_M, cacheStall_M, memStoreD_M, hit;
    logic [2:0]                 MemCtrl_M;
    logic [1:0]                 resultSrc_M;

    // Write Back
    logic [DATA_WIDTH-1:0]      pc_Plus4_W, ALUout_W, ReadMem_out_W, Result_W;
    logic [4:0]                 destinationReg_W;
    logic                       regWrite_W;
    logic [1:0]                 resultSrc_W;




always_ff @(posedge clk) begin
    $display(" ");

//     // Debug Fetch Stage
//     $display("Fetch Stage:");
    // $display("NEW Instruction: %h, Opcode: %b", instr_F, instr_F[6:0]); 
    $display("pc_F: %h, instr_F: %h", pc_F, instr_F);
// //     // $display("pc_Plus4_F: %h, pc_next_F: %h", pc_Plus4_F, pc_next_F);

// //     // $display("PCSrce_E: %b", PCSrc_E);

// //     // Debug Decode Stage
// //     $display("Decode Stage:");
// //     // $display("signextend opcode: %b, Sign extended value: %h", immSrc_D, ImmExt_D);    
// //     // $display("regwrite_D: %b", regWrite_D);
// //     // $display("regwrite_E: %b", regWrite_E);
// //     // $display("regwrite_M: %b", regWrite_M);
// //     // $display("regFileOut1_D: %h, regFileOut2_D: %h, ImmExt_D: %h", regFileOut1_D, regFileOut2_D, ImmExt_D);
// //     // $display("Instruction Decode: rd: %0d, rs1: %0d, rs2: %0d", instr_D[11:7], instr_D[19:15], instr_D[24:20]);
// //     // $display("resultSrc_D: %b", resultSrc_D);

// //     // Debug Execute Stage
// //     $display("Execute Stage:");
// //     // $display("Jump_E: %b, zero_E %b", jump_E, zero_E);
    // $display("ALUout_E: %h, ALU_in2_E: %h, mux4SrcA_OUT: %h", ALUout_E, ALU_in2_E, mux4SrcA_OUT);
// //     // $display("regFileOut1_E: %h, regFileOut2_E: %h", regFileOut1_E, regFileOut2_E);
// //     // $display("ALU Control: %b, ALU Src: %b", ALUcontrol_E, ALUsrc_E);
// //     // $display("memread_E %b", MemRead_E);
// //     // $display("resultSrc_E: %b", resultSrc_E);

// //     // Debug Memory Stage
// //     $display("Memory Stage:");
// //     $display("ALUout_M: %h, WriteData_M: %h, ReadMem_out_M: %h", ALUout_M, WriteData_M, ReadMem_out_M);
// //     $display("CacheStall: %b", cacheStall_M);
// //     $display("resultSrc_M: %b", resultSrc_M);
//     // $display("memread_M %b, Memory Control: %b", MemRead_M, MemCtrl_M);
//     $display("MemCtrl_D: %b, MemCtrl_E: %b,  MemCtrl_M: %b",  MemCtrl_D, MemCtrl_E, MemCtrl_M);
// //     if (memWrite_M) begin
// //         $display("Memory Write Enabled: Writing to memory: %h, Data: %h", ALUout_M, WriteData_M);
// //     end

// //     // Debug Writeback Stage
// //     $display("Writeback Stage:");
// //     $display("ALUout_W: %h, ReadMem_out_W: %h, pc_Plus4_W: %h", ALUout_W, ReadMem_out_W, pc_Plus4_W);
// //     $display("resultSrc_W: %b (0: ALUout_W, 1: ReadMem_out_W, 2: pc_Plus4_W)", resultSrc_W);
// //     // $display("regwrite: %b", regWrite_W);

    if (regWrite_W) begin
        $display("Register Write Enabled: Writing to Register: %0d, Data: %h", destinationReg_W, Result_W);
        // $display("This is a0:  ", a0);
    end
// //     // if (memWrite_M) begin
// //     //     $display("Memory Write Enabled: Writing to Memory: %0d, Data: %h", ALUout_M[17:0], WriteData_M);
// //     //     $display("This is a0:  ", a0);
// //     // end
//     $display("Memory Read out: %d", ReadMem_out_M);
        

// //     // Debug Hazard Unit
// //     // $display("Hazard Unit:");
// //     // $display("stall: %b, flush: %b", stall, flush);
    // $display("ForwardA_e: %b, ForwardB_e: %b", forwardA_e, forwardB_e);
end


                                                    // FETCH
InstrMem InstrMemory(
    .programC           (pc_F),
    .instr              (instr_F)
);

mux mux1PC (
    .in0                (pc_Plus4_F), 
    .in1                (pc_Target_E), 
    .sel                (PCSrc_E), 
    .out                (pc_next_F) 
);

pcInc pcIncrementBy4 (
    .pc                 (pc_F),
    .pcOut              (pc_Plus4_F)
); // DONE

pcReg pcRegister  (
    .stall              (stall), 
    .clk                (clk),
    .next_pc            (pc_next_F),
    .pc                 (pc_F)
); // DONE

pcf pcfetch_flipflop(
    .clk                (clk),
    .stall              (stall),   
    .flush              (flush), 

    .instruction        (instr_F),
    .pc_f               (pc_F),
    .pcPlus4_f          (pc_Plus4_F),

    .instruction_out    (instr_D),
    .pc_d               (pc_D),
    .pcPlus4_d          (pc_Plus4_D)
); // DONE

                                                    // DECODE
control controlUnit (
    .instruction        (instr_D),
    .stall              (stall),  
    .RegWrite           (regWrite_D),  
    .ALUSrc             (ALUsrc_D),   
    .ResultSrc          (resultSrc_D),  
    .MemCtrl            (MemCtrl_D),   
    .MemWrite           (memWrite_D),  
    .branch             (branch_D), 
    .jump               (jump_D),  
    .jalr               (jalr_D),  
    .MemStore           (memStoreD_D),
    .ALUCtrl            (ALUcontrol_D), 
    .IMMSrc             (immSrc_D),
    .MemRead            (MemRead_D),
    // .load               (loadD),
    // .PCSrc              (PCSrc_D)
); // DONE

signExtend signExtension (
    .instr          (instr_D),
    .ImmSrc         (immSrc_D),
    .ImmOp          (ImmExt_D)
); // DONE

RegFile Registers (
    .clk            (clk),
    .wren           (regWrite_W),
    .WriteReg       (destinationReg_W),
    .DAddress1      (instr_D[19:15]),
    .DAddress2      (instr_D[24:20]),
    .WData          (Result_W),
    .RData1         (regFileOut1_D),     
    .RData2         (regFileOut2_D),      
    .a0             (a0)      
);  // DONE


pcd pcdecode_flipflop(
    .clk                (clk),
    // .stall              (stall),           
    .flush              (flush),
    // control cascade
    .regWrite_d         (regWrite_D),
    .resultSrc_d        (resultSrc_D),
    .memWrite_d         (memWrite_D),
    .aluControl_d       (ALUcontrol_D),
    .aluSrc_d           (ALUsrc_D),
    .branch_d           (branch_D),
    .jump_d             (jump_D),
    .MemCtrl_d          (MemCtrl_D), 
    .jalr_d             (jalr_D),
    .MemStore_d         (memStoreD_D),
    .memRead_d          (MemRead_D),
    // .PCSrc_d            (PCSrc_D),   
    // data
    .rd1_d              (regFileOut1_D),
    .rd2_d              (regFileOut2_D),
    .pc_d               (pc_D),
    .rs1_d              (instr_D[19:15]),
    .rs2_d              (instr_D[24:20]), 
    .destinationReg_d   (instr_D[11:7]),
    .immExt_d           (ImmExt_D),
    .pcPlus4_d          (pc_Plus4_D),
    //outputs control cascade
    .regWrite_e         (regWrite_E),     
    .resultSrc_e        (resultSrc_E),    
    .memWrite_e         (memWrite_E),     
    .aluControl_e       (ALUcontrol_E),   
    .aluSrc_e           (ALUsrc_E),      
    .MemCtrl_e          (MemCtrl_E), 
    .jump_e             (jump_E),
    .jalr_e             (jalr_E), 
    .MemStore_e         (memStoreD_E),
    .branch_e           (branch_E),     
    .memRead_e          (MemRead_E),
    // .PCSrc_e            (PCSrc_E), 
    // outputs data
    .rd1_e              (regFileOut1_E), 
    .rd2_e              (regFileOut2_E), 
    .pc_e               (pc_E),
    .rs1_e              (rs1_E),
    .rs2_e              (rs2_E),
    .destinationReg_e   (destinationReg_E),
    .immExt_e           (ImmExt_E),
    .pcPlus4_e          (pc_Plus4_E)
); // DONE

                                                    // EXECUTE

mux jalr_mux (
    .in0                (pc_E),
    .in1                (regFileOut1_E),
    .sel                (jalr_E),
    .out                (jalrMux_out)
);

alu alu(
    .ALUop1             (mux4SrcA_OUT),
    .ALUop2             (ALU_in2_E),
    .ALUctrl            (ALUcontrol_E),
    .ALUout             (ALUout_E),
    .zero               (zero_E)
); // DONE


mux4 mux4SrcB (
    .in0                (regFileOut2_E),
    .in1                (Result_W),
    .in2                (ALUout_M),
    .sel                (forwardB_e),
    .out                (mux4SrcB_OUT)
); // DONE

mux4 mux4SrcA (
    .in0                (regFileOut1_E),
    .in1                (Result_W),
    .in2                (ALUout_M),
    .sel                (forwardA_e),
    .out                (mux4SrcA_OUT)
); // DONE

pcSrcGates pcSrcGate(
    .jump_e             (jump_E),
    .branch_e           (branch_E),
    .zero               (zero_E),
    .pcSrc_e            (PCSrc_E)
); // DONE

mux mux2ALU (
    .in0                (mux4SrcB_OUT),
    .in1                (ImmExt_E),
    .sel                (ALUsrc_E),
    .out                (ALU_in2_E)
); // DONE

pcAdder pc_e_Add_Imm (
    .pc                 (jalrMux_out),
    .immOp              (ImmExt_E),
    .branch_pc          (pc_Target_E)
); // DONE


pce pcexecute_flipflop (
    .clk                (clk),
    // control cascade
    .regWrite_e         (regWrite_E),
    .resultSrc_e        (resultSrc_E),
    .memWrite_e         (memWrite_E),
    .MemRead_e          (MemRead_E),
    .MemCtrl_e          (MemCtrl_E), 
    .MemStore_e         (memStoreD_E),
    // data
    .aluResult_e        (ALUout_E),
    .writeData_e        (mux4SrcB_OUT),
    .destinationReg_e   (destinationReg_E),
    .pcPlus4_e          (pc_Plus4_E), 
    //outputs control cascade
    .regWrite_m         (regWrite_M),
    .resultSrc_m        (resultSrc_M),
    .memWrite_m         (memWrite_M),
    .MemRead_m          (MemRead_M),
    .MemStore_m         (memStoreD_M),
    .MemCtrl_m          (MemCtrl_M), 
    // outputs data
    .aluResult_m        (ALUout_M),
    .writeData_m        (WriteData_M),
    .destinationReg_m   (destinationReg_M),
    .pcPlus4_m          (pc_Plus4_M)
); // DONE

                                                    // MEMORY

dataMemory datamemory (

    .clk (clk),
    .aluresultM (ALUout_M[17:0]), 
    .memwriteM (memWrite_M), 
    .memctrlM (MemCtrl_M),
    .memreadM (MemRead_M),
    .writedataM (WriteData_M), 

    .readdataM (memoryout)
);

cacheFSM cache_2 (
    .addressIn (ALUout_M),
    .dataIn (WriteData_M),
    .LoadMemory (MemRead_M),
    .storeMemory (memStoreD_M),
    .memwriteM (memWrite_M),
    .clk (clk),
    .memIn (memoryout),

    .Dataout (Cacheout),
    .hit (hit)
);

memoryCache memcache (
    .hit (hit),
    .Cachein (Cacheout),
    .Memoryin (memoryout),

    .Cacheout (ReadMem_out_M)
);

pcm pcmemory_flipflop(
    .clk                (clk),         
    // control cascade
    .regWrite_m         (regWrite_M),
    .resultSrc_m        (resultSrc_M),
    // data
    .aluResult_m        (ALUout_M),
    .readData_m         (ReadMem_out_M),
    .destinationReg_m   (destinationReg_M),
    .pcPlus4_m          (pc_Plus4_M),
    //outputs control cascade
    .regWrite_w         (regWrite_W),
    .resultSrc_w        (resultSrc_W),
    // outputs data
    .aluResult_w        (ALUout_W),
    .readData_w         (ReadMem_out_W),
    .destinationReg_w   (destinationReg_W),
    .pcPlus4_w          (pc_Plus4_W)
); // DONE

                                                    // WRITEBACK

mux4 mux4WriteBack (
    .in0                (ALUout_W),
    .in1                (ReadMem_out_W),
    .in2                (pc_Plus4_W),
    .sel                (resultSrc_W),
    .out                (Result_W)
);  // DONE

hazard hazardUnit (
    .rs1_e              (rs1_E),
    .rs2_e              (rs2_E),
    .rs1_d              (instr_D[19:15]),
    .rs2_d              (instr_D[24:20]),
    .rd_e               (destinationReg_E),
    .destReg_m          (destinationReg_M),
    .destReg_w          (destinationReg_W),
    .memoryRead_e       (MemRead_E),
    .regWrite_m         (regWrite_M),
    .regWrite_w         (regWrite_W),
    .jump_hazard        (jump_E),
    .zero_hazard        (zero_E),
    .forwardA_E         (forwardA_e),
    .forwardB_E         (forwardB_e),
    .stall              (stall),
    .flush              (flush)
); // DONE


endmodule
