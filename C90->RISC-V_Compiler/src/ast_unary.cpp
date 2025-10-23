#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_unary.hpp"

namespace ast {

    void Unary::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const
    {

        // & address-of operator
        // stream << "DEBUG: var.type = " << static_cast<int>(type) << "\n";

        if(UnaryOp_ == "&"){
            std::string memLocation = context.getMemLocation(cast_expression_->getId());
            stream << "addi " << destReg << ", s0, " << memLocation << std::endl;
        }

        // * pointer dereference

        if(UnaryOp_ == "*"){
            std::cout << "Goes to Unary * " << std::endl;
            std::string memLocation = context.getMemLocation(cast_expression_->getId());
            stream << "lw " << destReg << ", " << memLocation << "(s0)" << std::endl;
            stream << "lw " << destReg << ", 0(" << destReg << ")" << std::endl;

        }

        // - negation

        else if(UnaryOp_ == "-") {
            std::string a_reg = context.regAlloc();
            cast_expression_->EmitRISC(stream, context, a_reg);
            stream << "neg " << destReg << ", " << a_reg << std::endl;
            context.regDalloc(a_reg);
        }

        // ! logical not

        else if(UnaryOp_ == "!") {
            std::string a_reg = context.regAlloc();
            cast_expression_->EmitRISC(stream, context, a_reg);
            stream << "seqz " << destReg << ", " << a_reg << std::endl;
            context.regDalloc(a_reg);
        }

        // ~ bitwise not

        else if(UnaryOp_ == "~") {
            std::string a_reg = context.regAlloc();
            cast_expression_->EmitRISC(stream, context, a_reg);
            stream << "not " << destReg << ", " << a_reg << std::endl;
            context.regDalloc(a_reg);
        }

        // ++x

        else if(UnaryOp_ == "++"){
            std::string a_reg = context.regAlloc();
            std::string memLocation = context.getMemLocation(cast_expression_->getId());
            stream << "lw " << a_reg << ", " << memLocation << "(s0)" << std::endl;
            stream << "addi " << a_reg << ", " << a_reg << ", 1" << std::endl;
            stream << "sw " << a_reg << ", " << memLocation << "(s0)" << std::endl;
            stream << "mv " << destReg << ", " << a_reg << std::endl;
            context.regDalloc(a_reg);
        }

        // --x

        else if(UnaryOp_ == "--"){
            std::string a_reg = context.regAlloc();
            std::string memLocation = context.getMemLocation(cast_expression_->getId());
            stream << "lw " << a_reg << ", " << memLocation << "(s0)" << std::endl;
            stream << "addi " << a_reg << ", " << a_reg << ", -1" << std::endl;
            stream << "sw " << a_reg << ", " << memLocation << "(s0)" << std::endl;
            stream << "mv " << destReg << ", " << a_reg << std::endl;
            context.regDalloc(a_reg);
        }

        //need to check how to implement x++ and x--

    }

    EntitySpecifier Unary::getEntity() const
    {
        if (UnaryOp_ == "*")
        {
            return EntitySpecifier::POINTER_DEREFERENCE;
        }
        else if (UnaryOp_ == "&")
        {
            return EntitySpecifier::POINTER_ADDRESS;
        }
        else
        {
            return EntitySpecifier::UNARY;
        }
    }

    std::string Unary::getId() const
    {
        return cast_expression_->getId();
    }

    void Unary::Print(std::ostream &stream) const
    {
        stream << UnaryOp_;
        cast_expression_->Print(stream);
    }

    TypeSpecifier Unary::getType(Context &context) const
    {
        return cast_expression_->getType(context);
    }
}
