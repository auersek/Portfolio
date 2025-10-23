#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/logic_statements/ast_do_while.hpp"


void ast::DoWhile::EmitRISC(std::ostream &stream, Context &context) const
{
    std::string destinationRegister = context.regAlloc();
    std::string conditionLabel = context.labelAlloc("while");
    std::string statementLabel = context.labelAlloc("end");
    context.createLoop(statementLabel, conditionLabel);
    // stream << "j " << conditionLabel << std::endl;          // j L_3

    stream << statementLabel << ":" << std::endl;           // L_2:   (statement label)

    statement_->EmitRISC(stream, context);             // emit statement

    stream << conditionLabel << ":" << std::endl;                                    // L_3:  (condition label)

    condition_->EmitRISC(stream, context, destinationRegister);        // emit condition

    stream << "bnez " << destinationRegister << ", " << conditionLabel << std::endl; // bnez, x1, L_2

    context.exitLoop();
    context.regDalloc(destinationRegister);
}


void ast::DoWhile::Print(std::ostream &stream) const {
    stream << "do {" << std::endl;
    statement_->Print(stream);
    stream << "} (" << std::endl;
    condition_->Print(stream);
    stream << ")" << std::endl;
}


