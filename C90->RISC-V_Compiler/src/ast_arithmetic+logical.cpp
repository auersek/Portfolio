#include "../include/ast_arithmetic+logical.hpp"

// Add operator
namespace ast{

    void AddOp::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const
    {
        TypeSpecifier type1 = context.getVarType(a->getId());
        TypeSpecifier type2 = context.getVarType(b->getId());

        std::cout << context.getIsPointer(a->getId());

        if (context.getIsPointer(a->getId()))
        {
            std::cout << "calling arithmetic" << std::endl;
            int mem_size = TYPE_SIZE_INT;
            if(context.getVarType(a->getId()) == TypeSpecifier::INT){
                mem_size = TYPE_SIZE_INT;
            }
            else if (context.getVarType(a->getId()) == TypeSpecifier::FLOAT)
            {
                mem_size = TYPE_SIZE_FLOAT;
            }
            else if (context.getVarType(a->getId()) == TypeSpecifier::DOUBLE)
            {
                mem_size = TYPE_SIZE_DOUBLE;
            }
            else if (context.getVarType(a->getId()) == TypeSpecifier::CHAR)
            {
                mem_size = TYPE_SIZE_CHAR;
            }
            else{
                mem_size = 0;
            }
            std::string b_reg = context.regAlloc();
            a->EmitRISC(stream, context, destReg);
            b->EmitRISC(stream, context, b_reg);
            stream << "addi " << destReg << ", " << destReg << ", " << mem_size << std::endl;
            context.regDalloc(b_reg);
        }

        else if (context.getIsPointer(b->getId()))
        {
            std::cout << "calling arithmetic" << std::endl;
            int mem_size = TYPE_SIZE_INT;
            if(context.getVarType(b->getId()) == TypeSpecifier::INT){
                mem_size = TYPE_SIZE_INT;
            }
            else if (context.getVarType(b->getId()) == TypeSpecifier::FLOAT)
            {
                mem_size = TYPE_SIZE_FLOAT;
            }
            else if (context.getVarType(b->getId()) == TypeSpecifier::DOUBLE)
            {
                mem_size = TYPE_SIZE_DOUBLE;
            }
            else if (context.getVarType(b->getId()) == TypeSpecifier::CHAR)
            {
                mem_size = TYPE_SIZE_CHAR;
            }
            else{
                mem_size = 0;
            }
            std::string b_reg = context.regAlloc();
            a->EmitRISC(stream, context, destReg);
            b->EmitRISC(stream, context, b_reg);
            stream << "addi " << destReg << ", " << destReg << ", " << mem_size << std::endl;
            context.regDalloc(b_reg);
        }
        // if not pointer, regular operation
        else{
            if(type1 == TypeSpecifier::FLOAT || type2 == TypeSpecifier::FLOAT){         // floats
                std::string a_reg = context.floatRegAlloc();
                a->EmitRISC(stream, context, a_reg);
                stream << "fmv.s " << destReg << ", " << a_reg << std::endl;
                context.floatRegDalloc(a_reg);
                std::string b_reg = context.floatRegAlloc();
                b->EmitRISC(stream, context, b_reg);
                stream << "fadd.s " << destReg << ", " << destReg << ", " << b_reg<< std::endl;
                context.floatRegDalloc(b_reg);
            }
            else if(type1 == TypeSpecifier::DOUBLE || type2 == TypeSpecifier::DOUBLE){
                std::string b_reg = context.floatRegAlloc();
                a->EmitRISC(stream, context, destReg);
                b->EmitRISC(stream, context, b_reg);
                stream << "fadd.d " << destReg << ", " << destReg << ", " << b_reg << std::endl;
                context.floatRegDalloc(b_reg);
            }
            else{
                std::string b_reg = context.regAlloc();
                a->EmitRISC(stream, context, destReg);
                b->EmitRISC(stream, context, b_reg);
                stream << "add " << destReg << ", " << destReg << ", " << b_reg << std::endl;
                context.regDalloc(b_reg);
            }
        }
    }

void AddOp::Print(std::ostream &stream) const
{
    stream << "(";
    a->Print(stream);
    stream << " + ";
    b->Print(stream);
    stream << ")";
}

// sub operator

void SubOp::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const
{
    TypeSpecifier type1 = context.getVarType(a->getId());
    TypeSpecifier type2 = context.getVarType(b->getId());

    std::cout << context.getIsPointer(a->getId());

    if (context.getIsPointer(a->getId()))
    {
        std::cout << "calling arithmetic" << std::endl;
        int mem_size = TYPE_SIZE_INT;
        if(context.getVarType(b->getId()) == TypeSpecifier::INT){
            mem_size = TYPE_SIZE_INT;
        }
        else if (context.getVarType(b->getId()) == TypeSpecifier::FLOAT)
        {
            mem_size = TYPE_SIZE_FLOAT;
        }
        else if (context.getVarType(b->getId()) == TypeSpecifier::DOUBLE)
        {
            mem_size = TYPE_SIZE_DOUBLE;
        }
        else if (context.getVarType(b->getId()) == TypeSpecifier::CHAR)
        {
            mem_size = TYPE_SIZE_CHAR;
        }
        else{
            mem_size = 0;
        }
        std::string b_reg = context.regAlloc();
        b->EmitRISC(stream, context, b_reg);
        stream << "addi " << destReg << ", " << destReg << ", " << mem_size << std::endl;
        stream << "mul " << b_reg << ", " << b_reg << ", " << destReg << std::endl;
        stream << "add " << destReg << ", " << b_reg << ", zero" << std::endl;
        context.regDalloc(b_reg);

        std::string a_reg = context.regAlloc();
        a->EmitRISC(stream, context, a_reg);
        stream << "sub " << destReg << ", " << destReg << ", " << a_reg << std::endl;
        context.regDalloc(a_reg);
    }
    else if ((context.getIsPointer(b->getId()) && b->getEntity() != EntitySpecifier::POINTER_DEREFERENCE) || b->getEntity() == EntitySpecifier::POINTER_ADDRESS)
    {
        int mem_size = TYPE_SIZE_INT;
        if(context.getVarType(b->getId()) == TypeSpecifier::INT){
            mem_size = TYPE_SIZE_INT;
        }
        else if (context.getVarType(b->getId()) == TypeSpecifier::FLOAT)
        {
            mem_size = TYPE_SIZE_FLOAT;
        }
        else if (context.getVarType(b->getId()) == TypeSpecifier::DOUBLE)
        {
            mem_size = TYPE_SIZE_DOUBLE;
        }
        else if (context.getVarType(b->getId()) == TypeSpecifier::CHAR)
        {
            mem_size = TYPE_SIZE_CHAR;
        }
        else{
            mem_size = 0;
        }
        std::string a_reg = context.regAlloc();
        a->EmitRISC(stream, context, a_reg);
        stream << "addi " << destReg << ", " << destReg << ", " << mem_size << std::endl;
        stream << "mul " << a_reg << ", " << a_reg << ", " << destReg << std::endl;
        stream << "add " << destReg << ", " << a_reg << ", zero" << std::endl;
        context.regDalloc(a_reg);

        std::string b_reg = context.regAlloc();
        b->EmitRISC(stream, context, b_reg);
        stream << "sub " << destReg << ", " << destReg << ", " << b_reg << std::endl;
        context.regDalloc(b_reg);
    }
    else
    {
        if ((type1 == TypeSpecifier::INT || type2 == TypeSpecifier::INT))
        {
            std::string a_reg = context.regAlloc();
            a->EmitRISC(stream, context, a_reg);
            stream << "add " << destReg << ", " << a_reg << ", zero" << std::endl;
            context.regDalloc(a_reg);

            std::string b_reg = context.regAlloc();
            b->EmitRISC(stream, context, b_reg);
            stream << "sub " << destReg << ", " << destReg << ", " << b_reg << std::endl;
            context.regDalloc(b_reg);
        }
        else if (type1 == TypeSpecifier::CHAR || type2 == TypeSpecifier::CHAR)
        {
            std::string a_reg = context.floatRegAlloc();
            a->EmitRISC(stream, context, a_reg);
            stream << "sub " << destReg << ", " << a_reg << ", zero" << std::endl;
            context.regDalloc(a_reg);
            std::string b_reg = context.floatRegAlloc();
            b->EmitRISC(stream, context, b_reg);
            stream << "sub " << destReg << ", " << destReg << ", " << b_reg << std::endl;
            context.regDalloc(b_reg);
        }
        else if ((type1 == TypeSpecifier::FLOAT || type2 == TypeSpecifier::FLOAT))
        {
            std::string a_reg = context.floatRegAlloc();
            a->EmitRISC(stream, context, a_reg);
            stream << "fmv.s " << destReg << ", " << a_reg << std::endl;
            context.floatRegDalloc(a_reg);
            std::string b_reg = context.floatRegAlloc();
            b->EmitRISC(stream, context, b_reg);
            stream << "fsub.s " << destReg << ", " << destReg << ", " << b_reg << std::endl;
            context.floatRegDalloc(b_reg);
        }
        else if ((type1 == TypeSpecifier::DOUBLE || type2 == TypeSpecifier::DOUBLE))
        {
            std::string a_reg = context.floatRegAlloc();
            a->EmitRISC(stream, context, a_reg);
            stream << "fmv.d " << destReg << ", " << a_reg << std::endl;
            context.floatRegDalloc(a_reg);
            std::string b_reg = context.floatRegAlloc();
            b->EmitRISC(stream, context, b_reg);
            stream << "fsub.d " << destReg << ", " << destReg << ", " << b_reg << std::endl;
            context.floatRegDalloc(b_reg);
        }
    }
}


void SubOp::Print(std::ostream &stream) const
{
    stream << "(";
    a->Print(stream);
    stream << " - ";
    b->Print(stream);
    stream << ")";
}


// multiply operation

void MulOp::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const
{
    TypeSpecifier type1 = context.getVarType(a->getId());
    TypeSpecifier type2 = context.getVarType(b->getId());
    if (type1 == TypeSpecifier::INT || type2 == TypeSpecifier::INT)
    {
        std::string a_reg = context.regAlloc();
        a->EmitRISC(stream, context, a_reg);
        stream << "add " << destReg << ", " << a_reg << ", zero" << std::endl;
        context.regDalloc(a_reg);

        std::string b_reg = context.regAlloc();
        b->EmitRISC(stream, context, b_reg);
        stream << "mul " << destReg << ", " << destReg << ", " << b_reg << std::endl;
        context.regDalloc(b_reg);
    }
    else if (type1 == TypeSpecifier::CHAR || type2 == TypeSpecifier::CHAR)
    {
        std::string a_reg = context.regAlloc();
        a->EmitRISC(stream, context, a_reg);
        stream << "add " << destReg << ", " << a_reg << std::endl;
        context.regDalloc(a_reg);

        std::string b_reg = context.regAlloc();
        b->EmitRISC(stream, context, b_reg);
        stream << "mul " << destReg << ", " << destReg << ", " << b_reg << std::endl;
        context.regDalloc(b_reg);
    }
    else if ((type1 == TypeSpecifier::FLOAT || type2 == TypeSpecifier::FLOAT))
    {
        std::string a_reg = context.floatRegAlloc();
        a->EmitRISC(stream, context, a_reg);
        stream << "fmv.s " << destReg << ", " << a_reg << std::endl;
        context.floatRegDalloc(a_reg);
        std::string b_reg = context.floatRegAlloc();
        b->EmitRISC(stream, context, b_reg);
        stream << "fmul.s " << destReg << ", " << destReg << ", " << b_reg << std::endl;
        context.floatRegDalloc(b_reg);
    }
    else if ((type1 == TypeSpecifier::DOUBLE || type2 == TypeSpecifier::DOUBLE))
    {
        std::string a_reg = context.floatRegAlloc();
        a->EmitRISC(stream, context, a_reg);
        stream << "fmv.d " << destReg << ", " << a_reg << std::endl;
        context.floatRegDalloc(a_reg);
        std::string b_reg = context.floatRegAlloc();
        b->EmitRISC(stream, context, b_reg);
        stream << "fmul.d " << destReg << ", " << destReg << ", " << b_reg << std::endl;
        context.floatRegDalloc(b_reg);
    }
}

    void MulOp::Print(std::ostream &stream) const
    {
        stream << "(";
        a->Print(stream);
        stream << " * ";
        b->Print(stream);
        stream << ")";
    }


    // divide operation

    void DivOp::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const

    {
        TypeSpecifier type1 = context.getVarType(a->getId());
        TypeSpecifier type2 = context.getVarType(b->getId());
        if (type1 == TypeSpecifier::INT || type2 == TypeSpecifier::INT)
        {
            std::string a_reg = context.regAlloc();
            a->EmitRISC(stream, context, a_reg);
            stream << "add " << destReg << ", " << a_reg << ", zero" << std::endl;
            context.regDalloc(a_reg);

            std::string b_reg = context.regAlloc();
            b->EmitRISC(stream, context, b_reg);
            stream << "div " << destReg << ", " << destReg << ", " << b_reg << std::endl;
            context.regDalloc(b_reg);
        }
        else if (type1 == TypeSpecifier::CHAR || type2 == TypeSpecifier::CHAR)
        {
            std::string a_reg = context.regAlloc();
            a->EmitRISC(stream, context, a_reg);
            stream << "add " << destReg << ", " << a_reg << std::endl;
            context.regDalloc(a_reg);

            std::string b_reg = context.regAlloc();
            b->EmitRISC(stream, context, b_reg);
            stream << "div " << destReg << ", " << destReg << ", " << b_reg << std::endl;
            context.regDalloc(b_reg);
        }
        else if ((type1 == TypeSpecifier::FLOAT || type2 == TypeSpecifier::FLOAT))
        {
            std::string a_reg = context.floatRegAlloc();
            a->EmitRISC(stream, context, a_reg);
            stream << "fmv.s " << destReg << ", " << a_reg << std::endl;
            context.floatRegDalloc(a_reg);
            std::string b_reg = context.floatRegAlloc();
            b->EmitRISC(stream, context, b_reg);
            stream << "fdiv.s " << destReg << ", " << destReg << ", " << b_reg << std::endl;
            context.floatRegDalloc(b_reg);
        }
        else if ((type1 == TypeSpecifier::DOUBLE || type2 == TypeSpecifier::DOUBLE))
        {
            std::string a_reg = context.floatRegAlloc();
            a->EmitRISC(stream, context, a_reg);
            stream << "fmv.d " << destReg << ", " << a_reg << std::endl;
            context.floatRegDalloc(a_reg);
            std::string b_reg = context.floatRegAlloc();
            b->EmitRISC(stream, context, b_reg);
            stream << "fdiv.d " << destReg << ", " << destReg << ", " << b_reg << std::endl;
            context.floatRegDalloc(b_reg);
        }
    }

    void DivOp::Print(std::ostream &stream) const
    {
        stream << "(";
        a->Print(stream);
        stream << " / ";
        b->Print(stream);
        stream << ")";
    }


    //Bitwise And Operation
    void BitAndOp::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const

    {
        std::string a_reg = context.regAlloc();
        a->EmitRISC(stream, context, a_reg);
        stream << "add " << destReg << ", " << a_reg << ", zero" << std::endl;
        context.regDalloc(a_reg);
        std::string b_reg = context.regAlloc();
        b->EmitRISC(stream, context, b_reg);
        stream << "and " << destReg << ", " << destReg << ", " << b_reg << std::endl;
        context.regDalloc(b_reg);
    }

    void BitAndOp::Print(std::ostream &stream) const
    {
        stream << "(";
        a->Print(stream);
        stream << " & ";
        b->Print(stream);
        stream << ")";
    }

    TypeSpecifier BitAndOp::getType(Context &context) const
    {
        (void)context;
        return TypeSpecifier::INT;
    }


    //Bitwise Or Operation

    void BitOrOp::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const

    {
        std::string a_reg = context.regAlloc();
        a->EmitRISC(stream, context, a_reg);
        stream << "add " << destReg << ", " << a_reg << ", zero" << std::endl;
        context.regDalloc(a_reg);
        std::string b_reg = context.regAlloc();
        b->EmitRISC(stream, context, b_reg);
        stream << "or " << destReg << ", " << destReg << ", " << b_reg << std::endl;
        context.regDalloc(b_reg);
    }

    void BitOrOp::Print(std::ostream &stream) const
    {
        stream << "(";
        a->Print(stream);
        stream << " | ";
        b->Print(stream);
        stream << ")";
    }

    TypeSpecifier BitOrOp::getType(Context &context) const
    {
        (void)context;
        return TypeSpecifier::INT; // Default type for subtraction
    }

    //Bitwise Xor Operation

    void BitXorOp::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const

    {
        std::string a_reg = context.regAlloc();
        a->EmitRISC(stream, context, a_reg);
        stream << "add " << destReg << ", " << a_reg << ", zero" << std::endl;
        context.regDalloc(a_reg);
        std::string b_reg = context.regAlloc();
        b->EmitRISC(stream, context, b_reg);
        stream << "xor " << destReg << ", " << destReg << ", " << b_reg << std::endl;
        context.regDalloc(b_reg);
    }

    void BitXorOp::Print(std::ostream &stream) const
    {
        stream << "(";
        a->Print(stream);
        stream << " ^ ";
        b->Print(stream);
        stream << ")";
    }

    TypeSpecifier BitXorOp::getType(Context &context) const
    {
        (void)context;
        return TypeSpecifier::INT;
    }

    //Logical And Operation

    void LogAndOp::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const
    {
        if (a -> getType(context) == TypeSpecifier::INT || a -> getType(context) == TypeSpecifier::CHAR || a -> getType(context) == TypeSpecifier::UNSIGNED)
        {
            std::string true_label = context.labelAlloc("and_true");
            std::string false_label = context.labelAlloc("and_false");

            std::string a_reg = context.regAlloc();
            a->EmitRISC(stream, context, a_reg);
            stream << "beqz " << a_reg << ", " << false_label << std::endl;
            context.regDalloc(a_reg);

            std::string b_reg = context.regAlloc();
            b->EmitRISC(stream, context, b_reg);
            stream << "beqz " << b_reg << ", " << false_label << std::endl;
            stream << "li " << destReg << ", 1" << std::endl;
            stream << "j " << true_label << std::endl;
            context.regDalloc(b_reg);

            stream << false_label << ":" << std::endl;
            stream << "li " << destReg << ", 0" << std::endl;
            stream << true_label << ":" << std::endl;
        }
        else {
            std::string true_label = context.labelAlloc("and_true");
            std::string false_label = context.labelAlloc("and_false");

            std::string a_reg = context.regAlloc();
            a->EmitRISC(stream, context, a_reg);
            stream << "beqz " << a_reg << ", " << false_label << std::endl;
            context.regDalloc(a_reg);

            std::string b_reg = context.regAlloc();
            b->EmitRISC(stream, context, b_reg);
            stream << "beqz " << b_reg << ", " << false_label << std::endl;
            stream << "li " << destReg << ", 1" << std::endl;
            stream << "j " << true_label << std::endl;
            context.regDalloc(b_reg);

            stream << false_label << ":" << std::endl;
            stream << "li " << destReg << ", 0" << std::endl;
            stream << true_label << ":" << std::endl;
        }
    }

    void LogAndOp::Print(std::ostream &stream) const
    {
        stream << "(";
        a->Print(stream);
        stream << " && ";
        b->Print(stream);
        stream << ")";
    }

    TypeSpecifier LogAndOp::getType(Context &context) const
    {
        (void)context;
        return TypeSpecifier::INT;
    }

    //Logical Or Operation

    void LogOrOp::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const
    {
        if (a -> getType(context) == TypeSpecifier::INT || a -> getType(context) == TypeSpecifier::CHAR || a -> getType(context) == TypeSpecifier::UNSIGNED)
        {
            std::string true_label = context.labelAlloc("or_true");
            std::string false_label = context.labelAlloc("or_false");

            std::string a_reg = context.regAlloc();
            a->EmitRISC(stream, context, a_reg);
            stream << "bnez " << a_reg << ", " << true_label << std::endl;
            context.regDalloc(a_reg);

            std::string b_reg = context.regAlloc();
            b->EmitRISC(stream, context, b_reg);
            stream << "bnez " << b_reg << ", " << true_label << std::endl;
            stream << "li " << destReg << ", 0" << std::endl;
            stream << "j " << false_label << std::endl;
            context.regDalloc(b_reg);

            stream << true_label << ":" << std::endl;
            stream << "li " << destReg << ", 1" << std::endl;
            stream << false_label << ":" << std::endl;
        }
        else { //when we implement float and double
            std::string true_label = context.labelAlloc("or_true");
            std::string false_label = context.labelAlloc("or_false");

            std::string a_reg = context.regAlloc();
            a->EmitRISC(stream, context, a_reg);
            stream << "bnez " << a_reg << ", " << true_label << std::endl;
            context.regDalloc(a_reg);

            std::string b_reg = context.regAlloc();
            b->EmitRISC(stream, context, b_reg);
            stream << "bnez " << b_reg << ", " << true_label << std::endl;
            stream << "li " << destReg << ", 0" << std::endl;
            stream << "j " << false_label << std::endl;
            context.regDalloc(b_reg);

            stream << true_label << ":" << std::endl;
            stream << "li " << destReg << ", 1" << std::endl;
            stream << false_label << ":" << std::endl;
        }
    }

    void LogOrOp::Print(std::ostream &stream) const
    {
        stream << "(";
        a->Print(stream);
        stream << " || ";
        b->Print(stream);
        stream << ")";
    }

    TypeSpecifier LogOrOp::getType(Context &context) const
    {
        (void)context;
        return TypeSpecifier::INT;
    }

    //Modulus Operation

    void ModOp::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const
    {
        if (getType(context) == TypeSpecifier::INT)
        {
            std::string a_reg = context.regAlloc();
            a->EmitRISC(stream, context, a_reg);
            stream << "add " << destReg << ", " << a_reg << ", zero" << std::endl;
            context.regDalloc(a_reg);
            std::string b_reg = context.regAlloc();
            b->EmitRISC(stream, context, b_reg);
            stream << "rem " << destReg << ", " << destReg << ", " << b_reg << std::endl;
            context.regDalloc(b_reg);
        }
        else if (getType(context) == TypeSpecifier::UNSIGNED)
        {
            std::string a_reg = context.regAlloc();
            a->EmitRISC(stream, context, a_reg);
            stream << "add " << destReg << ", " << a_reg << ", zero" << std::endl;
            context.regDalloc(a_reg);
            std::string b_reg = context.regAlloc();
            b->EmitRISC(stream, context, b_reg);
            stream << "remu " << destReg << ", " << destReg << ", " << b_reg << std::endl;
            context.regDalloc(b_reg);
        }
    }

    void ModOp::Print(std::ostream &stream) const
    {
        stream << "(";
        a->Print(stream);
        stream << " % ";
        b->Print(stream);
        stream << ")";
    }

    TypeSpecifier ModOp::getType(Context &context) const
    {
        (void)context;
        return TypeSpecifier::INT; // Default type for subtraction
    }



} //namespace ast

