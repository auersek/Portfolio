#include "../include/ast_constant.hpp"

namespace ast {


void ast::IntConstant::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const
{
    (void)context;
    stream << "li " << destReg << ", " << value_ << std::endl;
}

void ast::FloatConstant::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const
{
    (void)context;
    stream << "flw " << destReg << ", " << value_ << std::endl;
}


void ast::IntConstant::Print(std::ostream& stream) const
{
    stream << value_;
}


void ast::FloatConstant::Print(std::ostream& stream) const
{
    stream << value_;
}

int IntConstant::getVal() const
{
    return value_;
}

} // namespace ast
