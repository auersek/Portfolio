#pragma once

#include "ast_node.hpp"

namespace ast{

    class IsEqual : public Node
    {
    private:
        NodePtr equality_expression_;
        NodePtr relational_expression_;

    public:
        IsEqual(NodePtr equality_expression, NodePtr relational_expression )
            : equality_expression_(std::move(equality_expression)),
              relational_expression_(std::move(relational_expression)){};
        virtual ~IsEqual()
        {
            delete equality_expression_;
            delete relational_expression_;
        };
        virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;
        virtual void Print(std::ostream &stream) const override;
        virtual TypeSpecifier getType(Context &context) const override;
    };

    class IsNotEqual : public Node
    {
        private:
        NodePtr equality_expression_;
        NodePtr relational_expression_;

    public:
        IsNotEqual(NodePtr equality_expression, NodePtr relational_expression )
            : equality_expression_(std::move(equality_expression)),
              relational_expression_(std::move(relational_expression)){};
        virtual ~IsNotEqual()
        {
            delete equality_expression_;
            delete relational_expression_;
        };
        virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;
        virtual void Print(std::ostream &stream) const override;
        virtual TypeSpecifier getType(Context &context) const override;
    };
}
