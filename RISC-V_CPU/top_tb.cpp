#include <cstdlib>
#include <utility>
#include <vector>
#include <iostream>

#include "cpu_testbench.h"
#include "vbuddy.cpp"


TEST_F(CpuTestbench, Testpdf)
{
    setupTest("5_pdf");
    setData("reference/gaussian.mem");
    initSimulation();
    std::vector<int> data; 
    bool distribution_complete = false;
    for (int i = 0; i < 800000; i++) {
        runSimulation(1);
        if (distribution_complete == false && top_->a0!= 0 ) {
                distribution_complete = true;
        } 
        else if (distribution_complete == true && 
                (data.empty() || top_->a0 != data.back())) {                     
            data.push_back(top_->a0);
        }
        if (data.size() >= 1024) {                                                 
            std::cout<<data.size()<<std::endl;
            break;
        }
    }
    for (int i = 0; i<data.size(); i++) {
        vbdPlot(data[i], 0, 255);                                        
        std::cout << data[i] << std::endl;
    }
}

int main(int argc, char** argv, char** env)
{
    if (vbdOpen() != 1) {
        return(-1);
    }
    vbdHeader("pdf_plots");
    
    testing::InitGoogleTest(&argc, argv);
    auto res = RUN_ALL_TESTS();
    return res;
    
    vbdClose();
    exit(0);
}