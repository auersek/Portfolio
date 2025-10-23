#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_variable.hpp"
#include <ostream>
#include <type_traits>


void ast::VariableDeclare::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const {
    (void)stream;


        if (!var_name_) {
            // Possibly print a debug message or just return
            stream << "# [Info] No var_name in VariableDeclare" << std::endl;
            return;
        }
        context.allocateStackSpace(var_name_->getId(), var_type_, false);
        var_name_->EmitRISC(stream, context, destReg);
    // }

}

void ast::VariableDeclare::Print(std::ostream &stream) const {
    stream << "int ";
    if (var_name_ != nullptr) {
        stream << var_name_->getId();
    } else {
        stream << "<null identifier>";
    }
    stream << ";" << std::endl;
}


ast::EntitySpecifier ast::VariableDeclare::getEntity() const
{
    return ast::EntitySpecifier::VARIABLE;
}


// ./scripts/test.py -m             multicore run
