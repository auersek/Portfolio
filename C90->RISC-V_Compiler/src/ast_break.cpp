#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_break.hpp"


void ast::BreakKeyWord::EmitRISC(std::ostream &stream, Context &context, std::string &) const {
    stream << "nop" << std::endl;        
    context.exitLoop();
}
void ast::BreakKeyWord::Print(std::ostream &stream) const {
    stream << "break;" << std::endl;
}


