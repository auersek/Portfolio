#pragma once

#include "ast_node.hpp"

namespace ast {
   class Unary : public Node
    {
    private:
        std::string UnaryOp_;
        NodePtr cast_expression_;

    public:

        Unary(std::string UnaryOp, NodePtr cast_expression) : UnaryOp_(std::move(UnaryOp)), cast_expression_(std::move(cast_expression)) {};
        virtual ~Unary()
        {
            delete cast_expression_;
        };


        virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;
        virtual void Print(std::ostream &stream) const override;
        virtual TypeSpecifier getType(Context &context) const override;
        virtual EntitySpecifier getEntity() const override;
        virtual std::string getId() const override;
    };
}
