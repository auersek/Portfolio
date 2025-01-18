module signExtend (
    input  logic [31:0] instr,
    input  logic [2:0]  ImmSrc,
    output logic [31:0] ImmOp
);

    logic [31:0] I_TYPE;
    logic [31:0] B_TYPE;
    logic [31:0] S_TYPE;
    logic [31:0] U_TYPE;
    logic [31:0] J_TYPE;
    logic [31:0] JALR_TYPE;

    always_comb begin
        ImmOp = 32'b0;
        I_TYPE = {{20{instr[31]}}, instr[31:20]};
        B_TYPE = {{20{instr[31]}}, instr[7], instr[30:25], instr[11:8], 1'b0};   
        U_TYPE = {instr[31:12], 12'b0};
        J_TYPE = {{12{instr[31]}}, instr[19:12], instr[20], instr[30:21], 1'b0};
        S_TYPE = {{20{instr[31]}}, instr[31:25], instr[11:7]};
        JALR_TYPE = {{27'b0}, instr[24:20]};
        case (ImmSrc)
            3'b000: ImmOp = I_TYPE; 
            3'b001: ImmOp = S_TYPE;
            3'b010: ImmOp = B_TYPE;
            3'b011: ImmOp = U_TYPE;
            3'b100: ImmOp = J_TYPE;
            3'b101: ImmOp = JALR_TYPE;
            default: $display("unexpected ImmSrc");
        endcase
    end


endmodule
