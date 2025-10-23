#pragma once

#include "ast_node.hpp"

namespace ast {

class IntConstant : public Node
{
private:
    int value_;

public:
    IntConstant(int value) : value_(value) {}

    void EmitRISC(std::ostream& stream, Context& context, std::string &destReg) const override;
    void Print(std::ostream& stream) const override;
    int getVal() const override;
};
class FloatConstant : public Node
{
private:
    float value_;

public:
    FloatConstant(float value) : value_(value) {}

    void EmitRISC(std::ostream& stream, Context& context, std::string &destReg) const override;
    void Print(std::ostream& stream) const override;
};

} // namespace ast
