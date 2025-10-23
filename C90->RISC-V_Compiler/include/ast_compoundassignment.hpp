#pragma once

#include <iostream>
#include <string>
#include "ast_node.hpp"
#include "ast_type_specifier.hpp"

namespace ast {

    class CompoundAssignment : public Node
    {
        private:
        NodePtr unary_expression_; // left hand side - variable
        std::string assignment_operator_; // assignment type like: =, +=
        NodePtr assignment_expression_; // right hand side - expression

        public:

        CompoundAssignment(NodePtr unary_expression, std::string assignment_operator, NodePtr assignment_expression) : unary_expression_(std::move(unary_expression)), assignment_operator_(std::move(assignment_operator)), assignment_expression_(std::move(assignment_expression)) {};
        virtual ~CompoundAssignment()
        {
            delete unary_expression_;
            delete assignment_expression_;
        };

        virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;
        virtual void Print(std::ostream &stream) const override;
        virtual TypeSpecifier getType(Context &context) const override;

    };
}

