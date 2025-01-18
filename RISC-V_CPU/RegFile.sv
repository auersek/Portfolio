module RegFile #(
    parameter   ADDRESS_WIDTH = 5,
                DATA_WIDTH = 32
)(
    input logic                     clk,
    input logic                     wren,
    input logic [ADDRESS_WIDTH-1:0] WriteReg,
    input logic [ADDRESS_WIDTH-1:0] DAddress1,
    input logic [ADDRESS_WIDTH-1:0] DAddress2,
    input logic [DATA_WIDTH-1:0]    WData,
    output logic [DATA_WIDTH-1:0]   RData1,        
    output logic [DATA_WIDTH-1:0]   RData2,      
    output logic [DATA_WIDTH-1:0]   a0     
);

    logic [DATA_WIDTH-1:0] ram_array [2**ADDRESS_WIDTH-1:0];

assign a0 = ram_array[10];

always_ff @ (negedge clk) begin
    // $display("register 0: %d", ram_array[0]);
    // if (ram_array[5] > 200)begin
    //     $display("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    // end

    // $display("t0: %d", ram_array[5]);
    // if (ram_array[6] <= 200) begin
    $display("t1: %d", ram_array[6]);
    // end
    $display("t2: %d", ram_array[7]);
    $display("s1: %d", ram_array[8]);
    $display("a0: %d", ram_array[10]);
    $display("a1: %d", ram_array[11]);
    $display("a2: %d", ram_array[12]);
    $display("a3: %d", ram_array[13]);
    $display("a4: %d", ram_array[14]);
    $display("a5: %d", ram_array[15]);
    $display("a6: %d", ram_array[16]);
    // $display("t3: %d", ram_array[28]);
    // $display("t4: %d", ram_array[29]);
end


always_ff @ (negedge clk) begin                             // ADD IF REGISTER IS ZERO THEN DONT WRITE
    if(wren && WriteReg != 5'b0) 
        ram_array[WriteReg] <= WData;
end

always_comb begin
    RData1 = ram_array[DAddress1];
    RData2 = ram_array[DAddress2]; 
end


endmodule
