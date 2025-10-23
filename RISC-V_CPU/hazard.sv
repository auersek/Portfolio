module hazard ( // notes say to check if source register in execute stage matches destination register in memory or writeback stage         
    input logic [4:0]       rs1_e, 
    input logic [4:0]       rs2_e,  
    input logic [4:0]       rs1_d, 
    input logic [4:0]       rs2_d,     
    input logic [4:0]       rd_e,
    input logic [4:0]       destReg_m,  
    input logic [4:0]       destReg_w,
    input logic             memoryRead_e,
    input logic             regWrite_m,     
    input logic             regWrite_w,   
    input logic             zero_hazard,   
    input logic             jump_hazard,
    output logic [1:0]      forwardA_E,
    output logic [1:0]      forwardB_E,  
    output logic            stall,          
    output logic            flush
);

// if the destination register is the same as the read address in memory or writeback, and write is enabled then forward

// forwardA_E = 2'b01 means resultW gets used as the aluInput1
// forwardB_E = 2'b01 means resultW gets used in the srcBe mux 0

// forwardA_E = 2'b10 means resultM gets used as the aluInput1
// forwardB_E = 2'b10 means resultM gets used in the srcBe mux 0
    
    // assign stall = (regWrite_m && (rs1_e == destReg_m || rs2_e == destReg_m)); maybe we can seperate these 2 
    // assign stall = (regWrite_m && (rs1_e == destReg_m || rs2_e == destReg_m || rs1_e == destReg_w || rs2_e == destReg_w));
    

//  logic [1:0] stall_counter;   IDEA

always_comb begin

    stall = 1'b0;
    flush = 1'b0;
    forwardA_E = 2'b00;
    forwardB_E = 2'b00;

                                    // FORWARDING
    // for forward A_E
    if (regWrite_m && (destReg_m != 0) && (destReg_m == rs1_e)) begin        
        forwardA_E = 2'b10;
    end 
    else if (regWrite_w && (destReg_w != 0) && (destReg_w == rs1_e)) begin         
        forwardA_E = 2'b01;
    end 
    else begin
        forwardA_E = 2'b00;
    end

    // for forward B_E
    if (regWrite_m && (destReg_m != 0) && (destReg_m == rs2_e)) begin              
        forwardB_E = 2'b10;
    end
    else if (regWrite_w && (destReg_w != 0) && (destReg_w == rs2_e)) begin             
        forwardB_E = 2'b01;
    end
    else begin
        forwardB_E = 2'b00;
    end

                                // STALL
    if (memoryRead_e && ((rd_e == rs1_d) || (rd_e == rs2_d))) begin                                 //   memoryRead_e
        stall = 1'b1;
    end 
    else begin
        stall = 1'b0;
    end

                                // FLUSH
    assign flush = (zero_hazard || jump_hazard);    

end

endmodule
