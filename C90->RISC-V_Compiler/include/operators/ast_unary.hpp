#pragma once

#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_node.hpp"

namespace ast {

class Unary : public Node
{
    private:
    std::string UnaryOp_;
    NodePtr Symbols_;

    public:

    Unary(std::string UnaryOp, NodePtr Symbols) : UnaryOp_(std::move(UnaryOp)), Symbols_(std::move(Symbols)) {};

    virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;

    virtual void Print(std::ostream &stream) const override;

    virtual TypeSpecifier getType(Context &context) const override;

    // virtual EntityType getEntity() const override;
};

}
