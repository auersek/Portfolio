#include "../include/ast_thans.hpp"

namespace ast {


    // Greater than

    void GreaterThan::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const
    {
        std::string b_reg = context.regAlloc();
        std::string a_reg = context.regAlloc();
        a->EmitRISC(stream, context, a_reg);
        b->EmitRISC(stream, context, b_reg);

        stream << "sgt " << destReg << ", " << a_reg << ", " << b_reg << std::endl;
        // stream << "andi " << destReg << ", " << destReg << ", 0xff" << std::endl;

        context.regDalloc(b_reg);

    }

    void GreaterThan::Print(std::ostream &stream) const
    {
        stream << "(";
        a->Print(stream);
        stream << " > ";
        b->Print(stream);
        stream << ")";
    }

    TypeSpecifier GreaterThan::getType(Context &context) const
    {
        (void)context;
        return TypeSpecifier::INT;
    }
    // Greater than or equal
    void GreaterThanEqual::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const
    {
        std::string b_reg = context.regAlloc();
        std::string a_reg = context.regAlloc();
        a->EmitRISC(stream, context, a_reg);
        b->EmitRISC(stream, context, b_reg);

        stream << "slt " << destReg << ", " << a_reg << ", " << b_reg << std::endl;
        stream << "xori " << destReg << ", " << destReg << ", 1" << std::endl;
        // stream << "andi " << destReg << ", " << destReg << ", 0xff" << std::endl;

        context.regDalloc(b_reg);
    }

    void GreaterThanEqual::Print(std::ostream &stream) const
    {
        stream << "(";
        a->Print(stream);
        stream << " >= ";
        b->Print(stream);
        stream << ")";
    }

    TypeSpecifier GreaterThanEqual::getType(Context &context) const
    {
        (void)context;
        return TypeSpecifier::INT;
    }

    // Less than
    void LessThan::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const
    {
        std::string a_reg = context.regAlloc();
        std::string b_reg = context.regAlloc();               // ONE OF THESE SHOULD BE EMITING DESTREG IM PRETTY SURE BECAUSE FOR_ZERO_V1 X7 is loaded into and then not used
        a->EmitRISC(stream, context, a_reg);
        b->EmitRISC(stream, context, b_reg);
        stream << "slt " << destReg << ", " << a_reg << ", " << b_reg << std::endl;
        // stream << "andi " << destReg << ", " << destReg << ", 0xff" << std::endl;
        context.regDalloc(b_reg);
    }

    void LessThan::Print(std::ostream &stream) const
    {
        stream << "(";
        a->Print(stream);
        stream << " < ";
        b->Print(stream);
        stream << ")";
    }

    TypeSpecifier LessThan::getType(Context &context) const
    {
        (void)context;
        return TypeSpecifier::INT;
    }

    // Less than equal
    void LessThanEqual::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const

    {
        std::string b_reg = context.regAlloc();
        std::string a_reg = context.regAlloc();
        a->EmitRISC(stream, context, a_reg);
        b->EmitRISC(stream, context, b_reg);

        stream << "sgt " << destReg << ", " << a_reg << ", " << b_reg << std::endl;
        stream << "xori " << destReg << ", " << destReg << ", 1" << std::endl;
        // stream << "andi " << destReg << ", " << destReg << ", 0xff" << std::endl;

        context.regDalloc(b_reg);
    }

    void LessThanEqual::Print(std::ostream &stream) const
    {
        stream << "(";
        a->Print(stream);
        stream << " <= ";
        b->Print(stream);
        stream << ")";
    }

    TypeSpecifier LessThanEqual::getType(Context &context) const
    {
        (void)context;
        return TypeSpecifier::INT;
    }


}
