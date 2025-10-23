#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_if_else.hpp"


void ast::IfElse::EmitRISC(std::ostream &stream, Context &context, std::string&) const
{
    std::string destinationRegister = context.regAlloc();
    std::string elseLabel = context.labelAlloc("else");
    std::string endLabel = context.labelAlloc("endif");

    condition_->EmitRISC(stream, context, destinationRegister);
    // stream << "mv " << destinationRegister << ", a0" << std::endl;
    stream << "beqz " << destinationRegister << ", " << elseLabel << std::endl;      // beqz x1, endif (branch equals zero)

    if_statement_->EmitRISC(stream, context, destinationRegister);
    stream << "j " << endLabel << std::endl;

    stream << elseLabel << ":" << std::endl;
    else_statement_->EmitRISC(stream, context,destinationRegister);

    stream << endLabel << ":" << std::endl;

    context.regDalloc(destinationRegister);
}

void ast::IfElse::Print(std::ostream &stream) const
{
    stream << "if (";                                // if (x == 5) return x else return x + y
    condition_->Print(stream);
    stream << ") {";
    if_statement_->Print(stream);
    stream << "} else {";
    else_statement_->Print(stream);
    stream << "}" << std::endl;
}
