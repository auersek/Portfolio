module InstrMem #(
    parameter   ADDRESS_WIDTH = 16,
                DATA_WIDTH = 32
)(
    input logic [31:0] programC,
    output logic [DATA_WIDTH-1:0]   instr 
);

    logic [7:0] instruction_mem [2**ADDRESS_WIDTH-1:0];

initial begin 
        $readmemh("../rtl/program.hex", instruction_mem);
end;


assign instr = {instruction_mem[programC[15:0]+3], instruction_mem[programC[15:0]+2], instruction_mem[programC[15:0]+1], instruction_mem[programC[15:0]]};



endmodule
