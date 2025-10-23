#pragma once


#include "ast_node.hpp"
#include "ast_type_specifier.hpp"

namespace ast {

    class LeftShift : public Node
    {
    private:
        NodePtr a;
        NodePtr b;


    public:
        LeftShift(NodePtr opa, NodePtr opb) : a(std::move(opa)), b(std::move(opb)) {}
        virtual ~LeftShift()
        {
            delete a;
            delete b;
        };

        virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;
        virtual void Print(std::ostream &stream) const override;
        virtual TypeSpecifier getType(Context &context) const override;
    };




    class RightShift : public Node
    {
    private:
            NodePtr a;
            NodePtr b;


    public:
        RightShift(NodePtr opa, NodePtr opb) : a(std::move(opa)), b(std::move(opb)) {}
        virtual ~RightShift()
        {
            delete a;
            delete b;
        };


        virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;
        virtual void Print(std::ostream &stream) const override;
        virtual TypeSpecifier getType(Context &context) const override;
    };

 }
