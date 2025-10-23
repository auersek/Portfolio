// #include "/workspaces/aurelersek/Desktop/langproc-cw-main/include/functions/ast_function_def.hpp"
// #include <ostream>


// void ast::FunctionDef::EmitRISC(std::ostream &stream, Context &context) const {

//     stream << ".text" << std::endl;
//     stream << ".globl f" << func_->getId() << std::endl;
//     std::string offset = context.takeMemory(TYPE_SIZE_RETURN_ADDRESS);
//     context.makeFuncReturnType(func_->getId(), specifiers_);        // necessary or can change???

//     func_->EmitRISC(stream, context);

//     stream << "sw ra, " << offset << "(s0)" << std::endl;           // use s0 or sp?   (sp is stack pointer)

//     if (statement_ != nullptr){
//         statement_->EmitRISC(stream, context);
//     }

//     stream << context.funcReturn() << ";" << std::endl;

//     stream << "lw ra, " << offset << "(s0)" << std::endl;
//     stream << "ret" << std::endl;

//     context.deallocateMemory(TYPE_SIZE_RETURN_ADDRESS);     // is this necessary or should be done in leavefunc?

//     context.leaveFunc(stream);
// }

// void ast::FunctionDef::Print(std::ostream& stream) const
// {
//     stream << specifiers_ << " ";           // type: int etc.

//     func_->Print(stream);                // function_name(int x, ...) part
//     stream << "() {" << std::endl;          // I dont think this is right, only right for func with no arguments
//     if (statement_ != nullptr)
//     {
//         statement_->Print(stream);       //inside of {  }
//     }
//     stream << "}" << std::endl;
// }

