#include "../include/ast_equals.hpp"

namespace ast {


void IsEqual::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const
{
    std::string a_reg = context.regAlloc();
    equality_expression_->EmitRISC(stream, context, a_reg);
    stream << "mv " << destReg << ", " << a_reg << std::endl;
    std::string b_reg = context.regAlloc();
    relational_expression_->EmitRISC(stream, context, b_reg);
    stream << "sub " << destReg << ", " << b_reg << ", " << destReg << std::endl;
    stream << "seqz " << destReg << ", " << destReg << std::endl;
}
void IsEqual::Print(std::ostream &stream) const {
    (void)stream;
}

TypeSpecifier IsEqual::getType(Context &context) const {
    (void)context;
    return TypeSpecifier::INT; }


void IsNotEqual::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const
{
    std::string a_reg = context.regAlloc();
    equality_expression_->EmitRISC(stream, context, a_reg);
    stream << "mv " << destReg << ", " << a_reg << std::endl;
    std::string b_reg = context.regAlloc();
    relational_expression_->EmitRISC(stream, context, b_reg);
    stream << "sub " << destReg << ", " << b_reg << ", " << destReg << std::endl;
    stream << "snez " << destReg << ", " << destReg << std::endl;
}

void IsNotEqual::Print(std::ostream &stream) const {
    (void)stream;
}

TypeSpecifier IsNotEqual::getType(Context &context) const {
    (void)context;
    return TypeSpecifier::INT; }



}
