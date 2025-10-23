#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_compoundassignment.hpp"
#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_context.hpp"

namespace ast {

    void CompoundAssignment::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const
    {
        std::string lhs_reg = context.regAlloc();
        std::string rhs_reg = context.regAlloc();

        TypeSpecifier result_type = getType(context);

        unary_expression_->EmitRISC(stream, context, lhs_reg);
        assignment_expression_->EmitRISC(stream, context, rhs_reg);

        if(assignment_operator_ == "="){
            stream << "mv " << lhs_reg << ", " << rhs_reg << std::endl;
        }
        else if(assignment_operator_ == "+="){
            stream << "add " << lhs_reg << ", " << lhs_reg << ", " << rhs_reg << std::endl;

        }
        else if(assignment_operator_ == "-="){
            stream << "sub " << lhs_reg << ", " << lhs_reg << ", " << rhs_reg << std::endl;

        }
        else if(assignment_operator_ == "*="){
            stream << "mul " << lhs_reg << ", " << lhs_reg << ", " << rhs_reg << std::endl;

        }
        else if(assignment_operator_ == "/="){
            stream << "div " << lhs_reg << ", " << lhs_reg << ", " << rhs_reg << std::endl;

        }

        else if(assignment_operator_ == "%="){
            stream << "rem " << lhs_reg << ", " << lhs_reg << ", " << rhs_reg << std::endl;

        }

        //bitwise

        else if(assignment_operator_ == "&="){
            stream << "and " << lhs_reg << ", " << lhs_reg << ", " << rhs_reg << std::endl;

        }

        else if(assignment_operator_ == "|="){
            stream << "or " << lhs_reg << ", " << lhs_reg << ", " << rhs_reg << std::endl;

        }

        else if(assignment_operator_ == "^="){
            stream << "xor " << lhs_reg << ", " << lhs_reg << ", " << rhs_reg << std::endl;

        }

        else if(assignment_operator_ == ">>="){
            stream << "sra " << lhs_reg << ", " << lhs_reg << ", " << rhs_reg << std::endl;

        }

        else if(assignment_operator_ == "<<="){
            stream << "sll " << lhs_reg << ", " << lhs_reg << ", " << rhs_reg << std::endl;

        }

        std::string MemLocation = context.getMemLocation(unary_expression_->getId());
        if (result_type == TypeSpecifier::CHAR)
        {
            stream << "sb " << lhs_reg << ", " << MemLocation << "(s0)" << std::endl;
        }
        else
        {
            stream << "sw " << lhs_reg << ", " << MemLocation << "(s0)" << std::endl;
        }

        destReg = lhs_reg; // needed to be added to update destReg

        context.regDalloc(rhs_reg);
        context.regDalloc(lhs_reg);

    }

    void CompoundAssignment::Print(std::ostream &stream) const
    {
        unary_expression_->Print(stream);
        stream << " " << assignment_operator_ << " ";
        assignment_expression_->Print(stream);
        stream << ";" << std::endl;
    }

    TypeSpecifier CompoundAssignment::getType(Context &context) const
    {
        return unary_expression_->getType(context);
    }

}
