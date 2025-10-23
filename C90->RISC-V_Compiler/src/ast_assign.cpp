#include "../include/ast_assign.hpp"
#include "../include/ast_context.hpp"

namespace ast {

    void Assignment::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const
    {
        std::string lhs_reg = context.regAlloc();
        std::string rhs_reg = context.regAlloc();

        TypeSpecifier type_l = context.getVarType(unary_expression_->getId());
        TypeSpecifier type_r = context.getVarType(assignment_expression_->getId());
        // stream << "DEBUG: var.type = " << static_cast<int>(type) << "\n";

        if (type_l == TypeSpecifier::FLOAT)
        {
            lhs_reg = context.floatRegAlloc();
        }
        else if (type_l == TypeSpecifier::DOUBLE)
        {
            lhs_reg = context.floatRegAlloc();
        }
        else if (type_l == TypeSpecifier::INT)
        {
            lhs_reg = context.regAlloc();
        }
        else if (type_l == TypeSpecifier::CHAR)
        {
            lhs_reg = context.regAlloc();
        }


        if (type_r == TypeSpecifier::FLOAT)
        {
            rhs_reg = context.floatRegAlloc();
        }
        else if (type_r == TypeSpecifier::DOUBLE)
        {
            rhs_reg = context.floatRegAlloc();
        }
        else if (type_r == TypeSpecifier::INT)
        {
            rhs_reg = context.regAlloc();
        }
        else if (type_r == TypeSpecifier::CHAR)
        {
            rhs_reg = context.regAlloc();
        }

        // Entity Array set flags

        if (unary_expression_->getEntity() == EntitySpecifier::ARRAY)
        {
            context.setArrayFlag(true);
            unary_expression_->EmitRISC(stream, context, lhs_reg);
            context.setArrayFlag(false);
        }
        else
        {
            unary_expression_->EmitRISC(stream, context, lhs_reg);
        }

        // Assignment operators

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

        std::cout << "FindMem in Assign " << unary_expression_->getId() << std::endl;
        std::string MemLocation = context.getMemLocation(unary_expression_->getId());

        if (type_l == TypeSpecifier::CHAR)
        {
            stream << "sb " << lhs_reg << ", " << MemLocation << "(s0)" << std::endl;
        }
        else
        {
            // stream << "DEBUG: ent.type = " << static_cast<int>(unary_expression_->getEntity()) << "\n";
            if (unary_expression_->getEntity() != EntitySpecifier::POINTER_DEREFERENCE){
                std::cout << "ParameterList check" << std::endl;
                stream << "sw " << lhs_reg << ", " << MemLocation << "(s0)" << std::endl;
            }

        }

        std::cout << "Array Index: " << context.getArrIndex() << std::endl;
        if(unary_expression_->getEntity() == EntitySpecifier::POINTER_DEREFERENCE){

            std::string pointer_mem = context.getMemLocation(unary_expression_->getId());
            std::cout << "Assign file lw" << std::endl;
            stream << "lw " << rhs_reg << ", " << pointer_mem << "(s0)" << std::endl;

            if(context.getVarType(unary_expression_->getId()) == TypeSpecifier::FLOAT){

                stream << "fsw " << lhs_reg << ", 0(" << rhs_reg << ")" << std::endl;
            }
            else if(context.getVarType(unary_expression_->getId()) == TypeSpecifier::DOUBLE){

                stream << "fsd " << lhs_reg << ", 0(" << rhs_reg << ")" << std::endl;
            }
            else if(context.getVarType(unary_expression_->getId()) == TypeSpecifier::CHAR){

                stream << "sb " << lhs_reg << ", 0(" << rhs_reg << ")" << std::endl;
            }
            else{
                std::cout << "Calling Assign SW" << std::endl;
                stream << "sw " << lhs_reg << ", 0(" << rhs_reg << ")" << std::endl;
            }
        }
        else if(unary_expression_->getEntity() == EntitySpecifier::ARRAY){

            TypeSpecifier array_types = context.getVarType(unary_expression_->getId());
            std::string index_reg = context.getArrIndex();
            if (array_types == TypeSpecifier::FLOAT)
            {
                stream << "fsw " << lhs_reg << ", 0(" << index_reg << ")" << std::endl;
            }
            else if (array_types == TypeSpecifier::DOUBLE)
            {
                stream << "fsd " << lhs_reg << ", 0(" << index_reg << ")" << std::endl;
            }
            else if (array_types == TypeSpecifier::CHAR)
            {
                stream << "sb " << lhs_reg << ", 0(" << index_reg << ")" << std::endl;
            }
            else
            {
                stream << "sw " << lhs_reg << ", 0(" << index_reg << ")" << std::endl;
            }
            context.regDalloc(index_reg);
            context.setArrIndex("");
        }

        destReg = lhs_reg; // needed to be added to update destReg

        context.regDalloc(rhs_reg);
        context.regDalloc(lhs_reg);

    }

    void Assignment::Print(std::ostream &stream) const
    {
        unary_expression_->Print(stream);
        stream << " " << assignment_operator_ << " ";
        assignment_expression_->Print(stream);
        stream << ";" << std::endl;
    }

    TypeSpecifier Assignment::getType(Context &context) const
    {
        return unary_expression_->getType(context);
    }

}
