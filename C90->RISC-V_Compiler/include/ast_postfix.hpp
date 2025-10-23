#pragma once

#include "ast_node.hpp"

namespace ast {
    class Postfixer : public Node
    {
        private:
        NodePtr primary_expression_;
        std::string op_;

        public:
        Postfixer(NodePtr primary_expression, std::string op) : primary_expression_(std::move(primary_expression)), op_(op){};

        virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;
        virtual void Print(std::ostream &stream) const override;
        //virtual TypeSpecifier getType(Context &context) const override;
    };

}
