module dataMemory #(parameter WA = 32, WAM = 17, WB = 8, WD = 32)(
    input logic clk,
    input logic [WAM:0] aluresultM, // aluresult formerly Ad
    input logic memwriteM, 
    input logic [WD-1:0] writedataM, //write data formerly DIn
    input logic [2:0] memctrlM,
    input logic memreadM,
    output logic [WD-1:0] readdataM
);

logic [WB-1:0] RamArray [2**WAM:0]; // stored in byte



initial begin
    $readmemh("data.hex", RamArray, 32'h10000);
end;

always_comb begin
    if(memreadM) begin
        if(memctrlM == 3'b011) begin
            readdataM = {24'b0, RamArray[aluresultM[17:0]]};
        end

        else begin
            readdataM = {
                RamArray[{aluresultM[17:2], 2'b11}],
                RamArray[{aluresultM[17:2], 2'b10}],
                RamArray[{aluresultM[17:2], 2'b01}],
                RamArray[{aluresultM[17:2], 2'b00}]
            };
        end
    end
        else begin
            readdataM = 32'b0;
        end
end

always_ff @(posedge clk) begin
    if(memwriteM && memctrlM == 3'b010) begin
        RamArray[aluresultM[17:0]] <= writedataM[7:0];
    end
    else if (memwriteM) begin
        RamArray[{aluresultM[17:2], 2'b00}] <= writedataM[7:0];
        RamArray[{aluresultM[17:2], 2'b01}] <= writedataM[15:8];
        RamArray[{aluresultM[17:2], 2'b10}] <= writedataM[23:16];
        RamArray[{aluresultM[17:2], 2'b11}] <= writedataM[31:24];
    end
end

endmodule

