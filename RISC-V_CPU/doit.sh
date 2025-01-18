#!/bin/bash

# Cleanup previous build artifacts
rm -rf obj_dir
rm -f onto.vcd

# Run Verilator for Verilog to C++, including C++ testbench and all required modules
verilator -Wall --cc --trace top.sv --exe top_tb.cpp

# Build the C++ code using the generated makefile
make -j -C obj_dir/ -f Vtop.mk Vtop

# Run the compiled Verilated model
obj_dir/Vtop

# ls /dev/tty.u*