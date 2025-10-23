#pragma once


#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_node.hpp"
#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_type_specifier.hpp"

namespace ast {

    class LeftShift : public Node
    {
        public:
            NodePtr a;
            NodePtr b;

        private:

        LeftShift(NodePtr opa, NodePtr opb) : a(std::move(opa)), b(std::move(opb)) {}

        virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;

        virtual void Print(std::ostream &stream) const override;
        virtual TypeSpecifier getType(Context &context) const override;
    };




    class RightShift : public Node
    {
        public:
            NodePtr a;
            NodePtr b;

        private:

        RightShift(NodePtr opa, NodePtr opb) : a(std::move(opa)), b(std::move(opb)) {}

        virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;

        virtual void Print(std::ostream &stream) const override;
        virtual TypeSpecifier getType(Context &context) const override;
    };

 }
