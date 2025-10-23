#include "../include/ast_postfix.hpp"

namespace ast {

   void Postfixer::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const
   {
        std::string tempReg = context.regAlloc();
        primary_expression_->EmitRISC(stream, context, tempReg);

        stream << "mv " << destReg << ", " << tempReg << std::endl;

        if(op_ == "++"){
            stream << "addi " << tempReg << ", " << tempReg << ", 1" << std::endl;
        }
        else if(op_ == "--"){
            stream << "addi " << tempReg << ", " << tempReg << ", -1" << std::endl;
        }
        stream << "sw " << tempReg << ", " << context.getMemLocation(primary_expression_->getId()) << "(s0)" << std::endl;
        context.regDalloc(tempReg);
   }

   void Postfixer::Print(std::ostream &stream) const
   {
        stream << "(";
        primary_expression_->Print(stream);
        stream << op_;
        stream << ")";
   }

//    TypeSpecifier Postfixer::getType(Context &context) const
//    {
//         return TypeSpecifier::INT;
//    }
}
