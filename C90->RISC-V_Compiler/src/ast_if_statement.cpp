#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_if_statement.hpp"

void ast::IfStatement::EmitRISC(std::ostream &stream, Context &context, std::string &) const
{
    std::string destinationRegister = context.regAlloc();
    std::string endLabel = context.labelAlloc("endif");

    condition_->EmitRISC(stream, context, destinationRegister);
    // stream << "mv " << destinationRegister << ", a0" << std::endl;
    stream << "beqz " << destinationRegister << ", " << endLabel << std::endl;      // beqz x1, endif

    statement_->EmitRISC(stream, context, destinationRegister);

    stream << endLabel << ":" << std::endl;

    context.regDalloc(destinationRegister);
}

void ast::IfStatement::Print(std::ostream &stream) const {
    stream << "if (";                            // if (x == 5) return x
    condition_->Print(stream);
    stream << ") ";
    statement_->Print(stream);
    stream << std::endl;
}


