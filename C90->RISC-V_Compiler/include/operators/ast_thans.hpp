#pragma once

#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_node.hpp"

namespace ast {

    class GreaterThan : public Node
{
    private:
    NodePtr a;
    NodePtr b;

    public:

    GreaterThan(NodePtr opa, NodePtr opb) : a(std::move(opa)), b(std::move(opb)) {}

    virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;

    virtual void Print(std::ostream &stream) const override;
    virtual TypeSpecifier getType(Context &context) const override;

};

class LessThan : public Node
{

    private:
    NodePtr a;
    NodePtr b;

    public:

    LessThan(NodePtr opa, NodePtr opb) : a(std::move(opa)), b(std::move(opb)) {}

    virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;

    virtual void Print(std::ostream &stream) const override;
    virtual TypeSpecifier getType(Context &context) const override;
};


class GreaterThanEqual : public Node
{
    private:
    NodePtr a;
    NodePtr b;

    public:

    GreaterThanEqual(NodePtr opa, NodePtr opb) : a(std::move(opa)), b(std::move(opb)) {}


    virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;

    virtual void Print(std::ostream &stream) const override;
    virtual TypeSpecifier getType(Context &context) const override;
};

class LessThanEqual : public Node
{
    private:
    NodePtr a;
    NodePtr b;

    public:

    LessThanEqual(NodePtr opa, NodePtr opb) : a(std::move(opa)), b(std::move(opb)) {}

    virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;

    virtual void Print(std::ostream &stream) const override;
    virtual TypeSpecifier getType(Context &context) const override;
};


}
