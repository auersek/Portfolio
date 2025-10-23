#include "../include/ast_function_call.hpp"
#include <string>

namespace ast {


void FunctionCall::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const {
    const Identifier* identifier = dynamic_cast<const Identifier*>(func_name_);
    std::string func_name = identifier->getId();
    std::cout << func_name << std::endl;
    if (parameters_names_ != nullptr){
        // (void)destReg;
        std::string storeReg;
        if (parameters_names_ != nullptr){
            int regCount = 0;
            for (auto param : parameters_names_->getNode()){
                if(regCount > 7){
                    storeReg = context.regAlloc();
                    param->EmitRISC(stream, context, storeReg);
                    stream << "sb " << storeReg << ", " << "(s0)" << std::endl;
                    context.regDalloc(storeReg);
                } else {
                    std::string destinationRegister = "a" + std::to_string(regCount);
                    param->EmitRISC(stream, context, destinationRegister);
                }
                regCount++;
            }
        }
        else{
            this->EmitRISC(stream, context, destReg);
        }
        if(destReg != ""){
            stream << "mv " << destReg << ", a0" << std::endl;
        }
        else{
            std::string tempReg = context.regAlloc();
            stream << "mv " << tempReg << ", a0" << std::endl;
            context.regDalloc(tempReg);
        }
    }
    // context.useRegister(stream);
    stream << "call " << func_name << std::endl;
    


}



void FunctionCall::Print(std::ostream &stream) const{
    func_name_->Print(stream);
    stream << "(";
    if (parameters_names_ != nullptr){
        for (auto param : parameters_names_->getNode()){   // i think this is correct not sure I added stuff to node.hpp
            param->Print(stream);
            stream << ", ";
        }
    }
}


}
