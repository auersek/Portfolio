#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/data_constructs/ast_enum_spec.hpp"


void ast::enum_spec::EmitRISC(std::ostream &stream, Context &context) const {
    context.createEnum(enum_name_);
    expr_->EmitRISC(stream, context);
    context.resEnum();
}

void ast::enum_spec::Print(std::ostream &stream) const {
    stream << "enum " << enum_name_ << " {" << std::endl;
    if (expr_ != nullptr){
        expr_->Print(stream);
    }
    stream << "}";
}


