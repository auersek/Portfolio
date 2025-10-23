#pragma once

#include <iostream>
#include <memory>


#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_node.hpp"
#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_type_specifier.hpp"

namespace ast {

    // add operator

    class AddOp : public Node
    {

    private:
        NodePtr a;
        NodePtr b;
        //a and b are now pointers

    public:
    AddOp(NodePtr opa, NodePtr opb) : a(std::move(opa)), b(std::move(opb)) {} //initialising the operands

        virtual ~AddOp() = default; //used to prevent memory leaks and cleans up memory when operation is destroyed

        virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;

        virtual void Print(std::ostream &stream) const override;
        virtual TypeSpecifier getType(Context &context) const override; //getType gets defined in hpp file -

    };



    // sub operator

    class SubOp : public Node
    {

    private:
        NodePtr a;
        NodePtr b;
        //a and b are now pointers

    public:
    SubOp(NodePtr opa, NodePtr opb) : a(std::move(opa)), b(std::move(opb)) {} //initialising the operands

        virtual ~SubOp() = default; //used to prevent memory leaks and cleans up memory when operation is destroyed

        virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;

        virtual void Print(std::ostream &stream) const override;
        virtual TypeSpecifier getType(Context &context) const override; //getType gets defined in hpp file -

    };

    // multiply operator

    class MulOp : public Node
    {

    private:
        NodePtr a;
        NodePtr b;
        //a and b are now pointers

    public:
    MulOp(NodePtr opa, NodePtr opb) : a(std::move(opa)), b(std::move(opb)) {} //initialising the operands

        virtual ~MulOp() = default; //used to prevent memory leaks and cleans up memory when operation is destroyed

        virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;

        virtual void Print(std::ostream &stream) const override;
        virtual TypeSpecifier getType(Context &context) const override; //getType gets defined in hpp file -

    };

    // divide operator

    class DivOp : public Node
    {

    private:
        NodePtr a;
        NodePtr b;
        //a and b are now pointers

    public:
    DivOp(NodePtr opa, NodePtr opb) : a(std::move(opa)), b(std::move(opb)) {} //initialising the operands

        virtual ~DivOp() = default; //used to prevent memory leaks and cleans up memory when operation is destroyed

        virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;

        virtual void Print(std::ostream &stream) const override;
        virtual TypeSpecifier getType(Context &context) const override; //getType gets defined in hpp file -

    };

    // bitwiseand operator

    class BitAndOp : public Node
    {

    private:
        NodePtr a;
        NodePtr b;
        //a and b are now pointers

    public:
    BitAndOp(NodePtr opa, NodePtr opb) : a(std::move(opa)), b(std::move(opb)) {} //initialising the operands

        virtual ~BitAndOp() = default; //used to prevent memory leaks and cleans up memory when operation is destroyed

        virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;

        virtual void Print(std::ostream &stream) const override;
        virtual TypeSpecifier getType(Context &context) const override; //getType gets defined in hpp file -

    };

    // bitwiseor operator

    class BitOrOp : public Node
    {

    private:
        NodePtr a;
        NodePtr b;
        //a and b are now pointers

    public:
    BitOrOp(NodePtr opa, NodePtr opb) : a(std::move(opa)), b(std::move(opb)) {} //initialising the operands

        virtual ~BitOrOp() = default; //used to prevent memory leaks and cleans up memory when operation is destroyed

        virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;

        virtual void Print(std::ostream &stream) const override;
        virtual TypeSpecifier getType(Context &context) const override; //getType gets defined in hpp file -

    };

    // bitwise xor operator

    class BitXorOp : public Node
    {

    private:
        NodePtr a;
        NodePtr b;
        //a and b are now pointers

    public:
    BitXorOp(NodePtr opa, NodePtr opb) : a(std::move(opa)), b(std::move(opb)) {} //initialising the operands

        virtual ~BitXorOp() = default; //used to prevent memory leaks and cleans up memory when operation is destroyed

        virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;

        virtual void Print(std::ostream &stream) const override;
        virtual TypeSpecifier getType(Context &context) const override; //getType gets defined in hpp file -

    };

    // logical and operator

    class LogAndOp : public Node
    {

    private:
        NodePtr a;
        NodePtr b;
        //a and b are now pointers

    public:
    LogAndOp(NodePtr opa, NodePtr opb) : a(std::move(opa)), b(std::move(opb)) {} //initialising the operands

        virtual ~LogAndOp() = default; //used to prevent memory leaks and cleans up memory when operation is destroyed

        virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;

        virtual void Print(std::ostream &stream) const override;
        virtual TypeSpecifier getType(Context &context) const override; //getType gets defined in hpp file -

    };

    // lgocial or operator

    class LogOrOp : public Node
    {

    private:
        NodePtr a;
        NodePtr b;
        //a and b are now pointers

    public:
    LogOrOp(NodePtr opa, NodePtr opb) : a(std::move(opa)), b(std::move(opb)) {} //initialising the operands

        virtual ~LogOrOp() = default; //used to prevent memory leaks and cleans up memory when operation is destroyed

        virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;

        virtual void Print(std::ostream &stream) const override;
        virtual TypeSpecifier getType(Context &context) const override; //getType gets defined in hpp file -

    };

    // modulus operator

    class ModOp : public Node
    {

    private:
        NodePtr a;
        NodePtr b;
        //a and b are now pointers

    public:
    ModOp(NodePtr opa, NodePtr opb) : a(std::move(opa)), b(std::move(opb)) {} //initialising the operands

        virtual ~ModOp() = default; //used to prevent memory leaks and cleans up memory when operation is destroyed

        virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;

        virtual void Print(std::ostream &stream) const override;
        virtual TypeSpecifier getType(Context &context) const override; //getType gets defined in hpp file -

    };

}
