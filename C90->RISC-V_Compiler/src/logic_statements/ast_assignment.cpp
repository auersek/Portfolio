// #include "/workspaces/aurelersek/Desktop/langproc-cw-main/include/ast_assignment.hpp"


// void ast::Assignment::EmitRISC(std::ostream &stream, Context &context) const {
//     std::string rhsReg = context.regAlloc();
//     assignment_expression_->EmitRISC(stream, context);
//     stream << "mv " << rhsReg << ", a0" << std::endl;

//     std::string lhsAddr = context.getMemLocation(unary_expression_->getId());

//     stream << "sw " << rhsReg << ", " << lhsAddr << "(sp)" << std::endl;

//     context.regDalloc(rhsReg);
// }

// void ast::Assignment::Print(std::ostream &stream) const
// {
//     unary_expression_->Print(stream);
//     stream << " " << assignment_operator_ << " ";
//     assignment_expression_->Print(stream);
//     stream << ";" << std::endl;
// }




// /*
//     stream << var_name_ << std::endl;
//     std::string destinationRegister = context.regAlloc();
//     TypeSpecifier varType = context.getVarType(var_name_);

//     if (varType == TypeSpecifier::INT || (varType == TypeSpecifier::INT && context.getIsPointer(var_name_))){
//         stream << "lw " << destinationRegister << ", " << context.getMemLocation(var_name_) << "(sp)" << std::endl;
//     }
//     else if (varType == TypeSpecifier::FLOAT){
//         stream << "flw " << destinationRegister << ", " << context.getMemLocation(var_name_) << "(sp)" << std::endl;
//     }
//     else if (varType == TypeSpecifier::CHAR){
//         stream << "lbu " << destinationRegister << ", " << context.getMemLocation(var_name_) << "(sp)" << std::endl;
//     }
//     else {
//         stream << "lw " << destinationRegister << ", " << context.getMemLocation(var_name_) << "(sp)" << std::endl;
//     }

// */
