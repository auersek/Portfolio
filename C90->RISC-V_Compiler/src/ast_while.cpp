#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_while.hpp"


void ast::WhileStatement::EmitRISC(std::ostream &stream, Context &context, std::string &) const
{
    std::string destinationRegister = context.regAlloc();
    std::string conditionLabel = context.labelAlloc("condition");
    std::string statementLabel = context.labelAlloc("statement");
    context.createLoop(conditionLabel, statementLabel);

    stream << "j " << conditionLabel << std::endl;          // j L_3

    stream << statementLabel << ":" << std::endl;           // L_2:   (statement label)
    std::string temp;
    if (statement_ != nullptr){
        statement_->EmitRISC(stream, context, destinationRegister);             // emit statement
    }
    stream << conditionLabel << ":" << std::endl;                                    // L_3:  (condition label)
    if (condition_ != nullptr){
        condition_->EmitRISC(stream, context, destinationRegister);        // emit condition
    }
    stream << "bne " << destinationRegister << ", zero, " << statementLabel << std::endl; // bnez, x1, L_2    " << destinationRegister

    context.exitLoop();
    context.regDalloc(destinationRegister);
}

void ast::ForStatement::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const
{

    expression_statement_->EmitRISC(stream, context, destReg);

    // std::string destReg = context.regAlloc();

    std::string startLabel = context.labelAlloc("for_");
    std::string conditionLabel = context.labelAlloc("condition_");
    std::string updateLabel = context.labelAlloc("update_");
    std::string endLabel = context.labelAlloc("endfor_");
    context.createForLoop(startLabel, endLabel, updateLabel);

    stream << "j " << conditionLabel << std::endl;

    stream << startLabel << ":" << std::endl;
    if (statement_) statement_->EmitRISC(stream, context, destReg);

    stream << updateLabel << ":" << std::endl;
    if (expression_ != nullptr)
    {
        expression_->EmitRISC(stream, context, destReg);
    }

    // Emit the end label

    stream << conditionLabel << ":" << std::endl;

    // Emit the condition
    if (loop_condition_->getEntity() == EntitySpecifier::SEMICOLON)
    {
        stream << "addi " << destReg << ", zero, 1" << std::endl;
    }
    else
    {
        loop_condition_->EmitRISC(stream, context, destReg);
    }
    // Emit the branch
    stream << "bnez " << destReg << ", " << startLabel << std::endl;

    //  Free the register
    stream << endLabel << ":" << std::endl;
    context.exitLoop();
    context.regDalloc(destReg);
}





void ast::WhileStatement::Print(std::ostream &stream) const
{
    stream << "while (";
    if (condition_ != nullptr){
        condition_->Print(stream);
    }
    stream << ") {";
    if (statement_ != nullptr){
    statement_->Print(stream);
    }
    stream << "}" << std::endl;
}

void ast::ForStatement::Print(std::ostream &stream) const
{
    stream << "for ( ";
    stream << ") {";
    if (statement_ != nullptr){
    statement_->Print(stream);
    }
    stream << "}" << std::endl;
}





