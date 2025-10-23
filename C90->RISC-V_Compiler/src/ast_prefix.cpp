#include "../include/ast_prefix.hpp"

namespace ast {

   void Prefixer::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const
   {
        std::string tempReg = context.regAlloc();
        primary_expression_->EmitRISC(stream, context, tempReg);

        if(op_ == "++"){
            stream << "addi " << tempReg << ", " << tempReg << ", 1" << std::endl;
        }
        else if(op_ == "--"){
            stream << "addi " << tempReg << ", " << tempReg << ", -1" << std::endl;
        }
        stream << "sw " << tempReg << ", " << context.getMemLocation(primary_expression_->getId()) << "(s0)" << std::endl;

        stream << "mv " << destReg << ", " << tempReg << std::endl;

        context.regDalloc(tempReg);
   }

   void Prefixer::Print(std::ostream &stream) const
   {
        stream << "(";
        primary_expression_->Print(stream);
        stream << op_;
        stream << ")";
   }

//    TypeSpecifier Prefixer::getType(Context &context) const
//    {
//         return TypeSpecifier::INT;
//    }
}
