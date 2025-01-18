module pcAdder #(
    parameter DATA_WIDTH = 32
)(
    input logic [DATA_WIDTH-1:0] pc,
    input logic  [DATA_WIDTH-1:0] immOp,
    output logic [DATA_WIDTH-1:0] branch_pc

);

always_ff 
    branch_pc = pc + immOp;

endmodule
