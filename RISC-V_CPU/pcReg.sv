module pcReg #(
    parameter DATA_WIDTH = 32
)(
    input logic                     stall,
    input logic	                    clk,
    input logic [DATA_WIDTH-1:0]    next_pc,
    output logic [DATA_WIDTH-1:0]   pc
);


always_ff @(posedge clk) begin
    if (!stall) begin
        pc <= next_pc;
    end
end

endmodule
