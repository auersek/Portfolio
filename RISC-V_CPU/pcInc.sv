module pcInc #(
    parameter DATA_WIDTH = 32
)(
    input logic [DATA_WIDTH-1:0] pc,
    output logic [DATA_WIDTH-1:0] pcOut
);

always_ff 
    pcOut = pc + {29'b0, 3'b100};

endmodule
