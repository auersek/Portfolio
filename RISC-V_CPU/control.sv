`include "define.sv"

module control (
    //Defining opcode, funct3 and funct7 like this makes it difficult to input full 32-bit instructions.
    input   logic [31:0] instruction,
    input   logic        stall,
    output  logic        RegWrite,  // Register file write enable
    output  logic        ALUSrc,    // ALU source selector
    output  logic [4:0]  ALUCtrl,   // ALU operation control
    output  logic [2:0]  IMMSrc,    // Immediate source selector
    output  logic [2:0]  MemCtrl,   // Memory operation control  
    output  logic        branch,     // branch flag
    output  logic        jump,       // jump flag
    output  logic        MemRead,
    output  logic        MemStore,
    output  logic        load,
    output  logic        jalr,
    output  logic        MemWrite,  // Memory write enable
    output  logic [1:0]  ResultSrc  // Result source selector   
);

    logic [6:0] opcode;    // Opcode from instruction
    logic [2:0] funct3;    // funct3 field from instruction
    logic [6:0] funct7;    // funct7 field from instruction

    //Assigning variables based on 32-bit instruction
    assign opcode = instruction[6:0];
    assign funct3 = instruction[14:12];
    assign funct7 = instruction[31:25];

    always_comb begin
        ALUCtrl     = `ALU_OPCODE_ADD;
        RegWrite    = 0;
        ALUSrc      = 0;
        ALUCtrl     = 0;
        IMMSrc      = 0;
        MemCtrl     = 0;
        MemRead     = 0;
        // PCSrc = `PC_NEXT;
        branch      = 0;     // branch flag
        jump        = 0;
        MemWrite    = 0;
        ResultSrc   = 0;
        jalr        = 0;

        case(opcode)
            //Register instructions
            7'b0110011: begin
                RegWrite  = 1;
                ALUSrc    = 0;
                MemWrite  = 0;
                ResultSrc = 0;
                
                // Decode ALU operation based on funct3 and funct7
                case(funct3)
                    3'b000: begin
                        case(funct7)
                            7'h00: begin 
                                ALUCtrl = `ALU_OPCODE_ADD;
                            end
                            7'h20: begin
                                ALUCtrl = `ALU_OPCODE_SUB;
                            end

                            default: $display ("Add/Sub faulty");
                        endcase
                    end
                    3'b100: begin
                        ALUCtrl = `ALU_OPCODE_XOR;
                    end

                    3'b110: begin
                        ALUCtrl = `ALU_OPCODE_OR;
                    end

                    3'b111: begin
                        ALUCtrl = `ALU_OPCODE_AND;
                    end

                    3'b001: begin
                        ALUCtrl = `ALU_OPCODE_LSL;
                    end
                    3'b101: begin
                        case(funct7)
                            7'h00: begin
                                ALUCtrl = `ALU_OPCODE_LSR;
                            end

                            7'h20: begin
                                ALUCtrl = `ALU_OPCODE_ASR;
                            end

                            default: $display ("LSR/ASR faulty");
                        endcase
                    end

                    3'b010: begin
                        ALUCtrl = `ALU_OPCODE_SLT;
                    end

                    3'b011: begin
                        ALUCtrl = `ALU_OPCODE_SLTU;
                    end

                    default: $display("R_TYPE instructions do not work");
                endcase
            end

            //Immediate instructions
            7'b0010011: begin
                RegWrite = 1;
                ALUSrc   = 1;  
                IMMSrc = `SIGN_EXTEND_I;
                
                case(funct3)
                    3'b000: begin
                        ALUCtrl = `ALU_OPCODE_ADD; // add instruction
                    end

                    3'b100: begin
                        ALUCtrl = `ALU_OPCODE_XOR; // xor instruction
                    end

                    3'b110: begin
                        ALUCtrl = `ALU_OPCODE_OR; // or instruction
                    end

                    3'b111: begin
                        ALUCtrl = `ALU_OPCODE_AND; // and instruction
                    end

                    3'b001: begin 
                        ALUCtrl = `ALU_OPCODE_LSL;
                    end

                    3'b101: begin 
                        case(funct7) 
                            7'h00: begin
                                ALUCtrl = `ALU_OPCODE_LSR;
                            end

                            7'h20: begin
                                ALUCtrl = `ALU_OPCODE_ASR;
                            end
                            default: $display("LSR and ASR IMM faulty");
                        endcase
                    end

                    3'b010: begin 
                        ALUCtrl = `ALU_OPCODE_SLT;
                    end

                    3'b011: begin 
                        ALUCtrl = `ALU_OPCODE_SLTU;
                    end

                    default: $display("I_TYPE instructions do not work");
                endcase
            end

            //I_TYPE Load instructions
            7'b0000011: begin
                RegWrite = 1;
                IMMSrc = `SIGN_EXTEND_I;
                ALUSrc = 1;
                MemWrite = 0;
                ResultSrc = 2'b01;
                case(funct3)
                    3'b000: begin                       //lb
                        MemCtrl = `MEM_B;
                        MemRead = 1;
                        load = 1;
                    end
                    3'b001: begin                       //lh
                        MemCtrl = `MEM_H;
                        MemRead = 1;
                        load = 1;
                    end
                    3'b010: begin                       //lw
                        MemCtrl = `MEM_W;
                        MemRead = 1;
                        load = 1;
                    end                                 //lbu
                    3'b100: begin 
                        MemCtrl = `MEM_BU;
                        MemRead = 1;
                        load = 1;
                    end                                 //lhu                              
                    3'b101: begin 
                        MemCtrl = `MEM_HU;
                        MemRead = 1;
                        load = 1;
                    end
                    default: $display("Load instructions faulty");
                endcase
            end
            7'b0100011: begin               //Store instructions
                RegWrite = 0;
                ALUSrc = 1;
                ALUCtrl = `ALU_OPCODE_ADD;
                IMMSrc = `SIGN_EXTEND_S;
                MemWrite = 1;
                case(funct3)
                    3'b000: begin
                        MemCtrl = `MEM_B; // sb instruction
                        MemStore = 1;
                    end

                    3'b001: begin
                        MemCtrl = `MEM_H; // sh instruction
                        MemStore = 1;
                    end

                    3'b010: begin
                        MemCtrl = `MEM_W; // sw instruction
                        MemStore = 1;
                    end
                    default: $display("Store instructions faulty");
                endcase
            end
            //Yet to check B_TYPE and J_TYPE
            7'b1100011: begin
                RegWrite = 0;
                ALUSrc   = 0;
                IMMSrc = `SIGN_EXTEND_B;
                branch = 1;
                case(funct3)
                    3'b000: begin
                        // PCSrc = `PC_COND_BRANCH;        // beq instruction
                        ALUCtrl = `ALU_OPCODE_BEQ;      //Using SUB to find whether is EQ
                    end
                    3'b001: begin
                        // PCSrc = `PC_INV_COND_BRANCH;    // bne instruction
                        ALUCtrl = `ALU_OPCODE_BNE;      //Using SUB to find whether is EQ and inverting the condition for HIGH
                    end
                    3'b100: begin
                        // PCSrc = `PC_INV_COND_BRANCH;    // blt instruction
                        ALUCtrl = `ALU_OPCODE_BLT;      //Using SLT and inverting the condition for HIGH
                    end
                    3'b101: begin
                        // PCSrc = `PC_COND_BRANCH;        // bge instruction
                        ALUCtrl = `ALU_OPCODE_BGE;      //Using SLT
                    end
                    3'b110: begin
                        // PCSrc = `PC_INV_COND_BRANCH;    // bltu instruction
                        ALUCtrl = `ALU_OPCODE_BLTU;     //Using SLT with Unsigned and inverting the condition for HIGH
                    end
                    3'b111: begin
                        // PCSrc = `PC_COND_BRANCH;        // bgeu instruction
                        ALUCtrl = `ALU_OPCODE_BGEU;     //Using SLT with Unsigned
                    end
                    default: $display("Warning: undefined B-type instruction");
                endcase
            end
            7'b1101111: begin    // jump and link
                RegWrite = 1;
                ALUSrc   = 1;
                IMMSrc = `SIGN_EXTEND_J;
                jump = 1;
                ResultSrc = 2;
                // PCSrc = `PC_ALWAYS_BRANCH;
            end

            7'b1100111: begin   // jump and link register
                RegWrite = 0;
                ALUSrc   = 1;
                IMMSrc = `SIGN_EXTEND_JALR;
                jalr = 1;
                jump = 1;
                ResultSrc = 2;
                // PCSrc = `PC_ALWAYS_BRANCH;
            end
            7'b0110111: begin 
                RegWrite = 1;
                ALUSrc   = 1;
                IMMSrc = `SIGN_EXTEND_U;
                ALUCtrl = `ALU_OPCODE_LUI; // load upper immediate
            end
            7'b0010111: begin 
                RegWrite = 1;
                ALUSrc   = 1;
            end
            // default: $display("just flushed");   //"err: Instruction: %h, Opcode: %b", instruction, opcode
        endcase                                                  
        if (stall) begin                                                               
            MemWrite = 0;
            MemRead = 0;
            MemStore = 0;
            RegWrite = 0;
        end
    end
endmodule
