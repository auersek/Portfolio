#include "../include/ast_shift.hpp"

namespace ast {

    void LeftShift::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const
    {
        a->EmitRISC(stream, context, destReg);

        std::string b_reg = context.regAlloc();
        b->EmitRISC(stream, context, b_reg);

        stream << "sll " << destReg << ", " << destReg << ", " << b_reg << std::endl;

        context.regDalloc(b_reg);

    }

    void LeftShift::Print(std::ostream &stream) const
    {
        stream << "(";
        a->Print(stream);
        stream << " << ";
        b->Print(stream);
        stream << ")";
    }

    TypeSpecifier LeftShift::getType(Context &context) const
    {
        (void)context;
        return TypeSpecifier::INT;
    }


    void RightShift::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const
    {
        a->EmitRISC(stream, context, destReg);

        std::string b_reg = context.regAlloc();
        b->EmitRISC(stream, context, b_reg);

        if (getType(context) == TypeSpecifier::INT) {
            stream << "sra " << destReg << ", " << destReg << ", " << b_reg << std::endl;
        } else {
            stream << "srl " << destReg << ", " << destReg << ", " << b_reg << std::endl;
        }

        context.regDalloc(b_reg);

    }

    void RightShift::Print(std::ostream &stream) const
    {
        stream << "(";
        a->Print(stream);
        stream << " >> ";
        b->Print(stream);
        stream << ")";
    }

    TypeSpecifier RightShift::getType(Context &context) const
    {
        (void)context;
        return TypeSpecifier::INT;
    }

}

