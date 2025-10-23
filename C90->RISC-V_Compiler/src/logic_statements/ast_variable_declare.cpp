// #include "/workspaces/aurelersek/Desktop/langproc-cw-main/include/ast_variable_declare.hpp"
// #include <stdexcept>

// void ast::VariableDeclare::EmitRISC(std::ostream &stream, Context &context, std::string &) const {

//     if (var_type_ == TypeSpecifier::INT) {
//         context.allocateStackSpace(var_name_->getId(), var_type_, false);
//         var_name_->EmitRISC(stream, context);
//     }
//     else if (var_type_ == TypeSpecifier::FLOAT) {
//         context.allocateStackSpace(var_name_->getId(), var_type_, false);
//         var_name_->EmitRISC(stream, context);
//     }
//     else if (var_type_ == TypeSpecifier::CHAR) { // Differentiating between `char` and `string` is context-dependent
//         context.allocateStackSpace(var_name_->getId(), var_type_, false);
//         var_name_->EmitRISC(stream, context);
//     }
//     else {
//         throw std::runtime_error("Invalid type in VariableDeclare");
//     }
// }


// //


// void ast::VariableDeclare::Print(std::ostream &stream) const {
//     // stream << var_type_ << " ";
//     // for (const auto& var : var_name_->getNode()) {
//     //     std::string var_name = var->getId();
//     //     stream << var_name << ", ";         // what to do about last variable maybe doesnt matter
//     // }
//     stream << ";" << std::endl;
// };

