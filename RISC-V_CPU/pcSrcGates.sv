module pcSrcGates(
    input logic         jump_e,
    input logic         branch_e,
    input logic         zero,
    output logic        pcSrc_e
);

assign pcSrc_e = (jump_e || (branch_e && zero));

endmodule
