module alu #(
    parameter DATA_WIDTH = 32
)(
    input logic [DATA_WIDTH-1:0] ALUop1,
    input logic [DATA_WIDTH-1:0] ALUop2,
    input logic [4:0] ALUctrl,
    output logic [DATA_WIDTH-1:0] ALUout,
    output logic zero
);

    logic signed [DATA_WIDTH-1:0] signed_ALUop1;
    logic signed [DATA_WIDTH-1:0] signed_ALUop2;

    assign signed_ALUop1 = ALUop1;
    assign signed_ALUop2 = ALUop2;

    always_comb begin
        ALUout = 0;  
        zero = 0;   

        case (ALUctrl)
            5'b00000: ALUout = ALUop1 + ALUop2;                     // Addition
            5'b00001: ALUout = ALUop1 - ALUop2;                     // Subtraction
            5'b00010: ALUout = ALUop1 & ALUop2;                     // AND
            5'b00011: ALUout = ALUop1 | ALUop2;                     // OR
            5'b00100: ALUout = ALUop1 ^ ALUop2;                     // XOR
            5'b00101: ALUout = ALUop1 << ALUop2[4:0];               // Logical shift left
            5'b00110: ALUout = ALUop1 >> ALUop2[4:0];               // Logical shift right
            5'b00111: ALUout = signed_ALUop1 >>> ALUop2[4:0];       // Arithmetic shift right
            5'b01000: ALUout = (signed_ALUop1 < signed_ALUop2) ? 1 : 0; // Set less than (signed)
            5'b01001: ALUout = (ALUop1 < ALUop2) ? 1 : 0;           // Set less than (unsigned)
            5'b01010: ALUout = ALUop2;                              // lui
            5'b01011: zero = (ALUop1 == ALUop2); 
            5'b01100: zero = (ALUop1 != ALUop2);
            5'b01101: zero = (signed_ALUop1 < signed_ALUop2) ? 1 : 0;
            5'b01110: zero = (signed_ALUop1 > signed_ALUop2) ? 1 : 0;
            5'b01111: zero = (ALUop1 < ALUop2) ? 1 : 0; 
            5'b10000: zero = (ALUop1 > ALUop2) ? 1 : 0; 
 
            default: $display("Unexpected opcode: %b", ALUctrl);   
        endcase

        // Set zero flag
        // zero = (ALUout == 0);
    end

endmodule
