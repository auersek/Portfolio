#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_direct_declarator.hpp"

namespace ast {

    void DirectDeclarator::EmitRISC(std::ostream& stream, Context& context, std::string &) const
    {
        std::string temp;
        context.addToScope(stream);

        context.initalizeStack(stream);

        // Put parameters on the stack
        if (parameter_list_ != nullptr)
        {
            parameter_list_->EmitRISC(stream, context, temp);
        }
        // }
    }

    std::string DirectDeclarator::getId() const { return identifier_->getId(); }

    void DirectDeclarator::Print(std::ostream& stream) const
    {
        if (identifier_) {
            identifier_->Print(stream);
        }

        if (parameter_list_ != nullptr) {
            // stream << "THERE IS A LIST";
            // stream << parameter_list_->getId();
            parameter_list_->Print(stream);
        }
    }

} // namespace ast
