module dataMemCached #(
    parameter   ADDRESS_WIDTH = 18,
                DATA_WIDTH = 32
)(
    input logic                         clk,
    input logic [2:0]                   memCtrl,
    input logic [ADDRESS_WIDTH-1:0]     Address,           
    input logic                         memReadAllowed,    
    input logic                         memWriteAllowed,    
    input logic [DATA_WIDTH-1:0]        WriteData,         
    output logic [DATA_WIDTH-1:0]       ReadData,           
    output logic                        ready               
);

    logic [7:0] data_mem [2**17:0];

initial begin 
        $display("Loading data into memory");
        $readmemh("../rtl/gaussian.mem", data_mem, 17'h10000);
end;

// logic [7:0] MEMM;
// logic [7:0] MEM;

// assign MEMM = data_mem[65536];
// assign MEM = data_mem[65537];

    always_ff @* begin 
        if(memReadAllowed || memWriteAllowed) begin 
            ready = 1;
        end
        else begin 
            ready = 0;
        end
        if(memReadAllowed) begin
            // $display("Memory Read Addresses and Values:");
            // $display("Address Byte 0: 00010000, Value: %h", array[18'h10000]);
            // $display("Address Byte 1: 00010001, Value: %h", array[18'h10001]);
            // $display("MemCtrl: %b", MemCtrl);
            if(memCtrl == 3'b000) begin 

                ReadData = {{24{data_mem[Address][7]}}, data_mem[Address]}; 
            end
            if(memCtrl == 3'b011) begin 

                ReadData = {24'b0, data_mem[Address[17:0]]};
            end
            else begin 
                ReadData = {data_mem[Address+3], data_mem[Address+2], data_mem[Address+1], data_mem[Address]};
            end
        end
        else begin 
            ReadData = 0;
        end
    end

    always_ff @* begin 
        // $display("Memory Address:");
        if (memWriteAllowed) begin
            $display("Address: %d, Data written: %d", Address, WriteData);
        end
        // $display("Data: %d", WriteData);
        //         $display("Memory Address:");
        if (memReadAllowed) begin
            $display("Address: %d, Data read: %d", Address, ReadData);
        end
        // $display("Data: %d", ReadData);
        
        
        // $display("Address Byte 0: 00140, Value: %h", data_mem [18'h00140]);
        // $display("Address Byte 1: 00140, Value: %h", data_mem [18'h00142]);
        // $display("memcontrol %b", memCtrl);
    end

    always_ff @(posedge clk) begin 
        if (memWriteAllowed & (memCtrl == 3'b000)) begin 
            data_mem[Address] <= WriteData[7:0]; 
        end 
        else if (memWriteAllowed) begin
            data_mem[Address]   <= WriteData[7:0];       
            data_mem[Address+1] <= WriteData[15:8];      
            data_mem[Address+2] <= WriteData[23:16];     
            data_mem[Address+3] <= WriteData[31:24];    
        end
    end

endmodule

