// #include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_parameter_list.hpp"
// #include "stdlib.h"

// namespace ast {

//     void ParameterList::EmitRISC(std::ostream &stream, Context &context, std::string &) const {
//         int i = 0;
//         std::string offset;
//         for (auto param : param_list_.getNode()) {
//             if ((i <= 7) & (param != nullptr)){
//                 offset = context.takeMemory(TYPE_SIZE_INT);
//                 stream << "sw a" << i << ", " << offset << "(sp)" << std::endl;
//                 i++;
//             }
//         }
//     }

//     void ParameterList::Print(std::ostream &stream) const {
//         stream << "hellow world";
//     }

// }
