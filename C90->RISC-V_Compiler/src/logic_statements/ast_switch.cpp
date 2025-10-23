#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/logic_statements/ast_switch.hpp"
            // SIMILAR STRUCTURE TO IF STATEMENTS

void ast::Switch::EmitRISC(std::ostream &stream, Context &context) const {

    context.createSwitch();

    std::string destReg = context.regAlloc();

    expr_->EmitRISC(stream, context, destReg);

    for(auto &cases : list_->getNode()){
        cases->EmitRISC(stream, context, destReg);
    }
    stream << "j " << context.defaultLabel() << std::endl;          // whats the point default label is never set?

    stream << context.switchLabel() << ":" << std::endl;

    context.regDalloc(destReg);
    context.exit_s();
}

void ast::Switch::Print(std::ostream &stream) const {
    stream << "switch (";
    expr_->Print(stream);
    stream << ") ";
    list_->Print(stream);
    stream << std::endl;
}




