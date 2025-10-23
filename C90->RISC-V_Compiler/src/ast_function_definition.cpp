#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_function_definition.hpp"
#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_direct_declarator.hpp"
#include <cstddef>

namespace ast {


void FunctionDefinition::EmitRISC(std::ostream& stream, Context& context, std::string &) const
{
    auto directDecl = dynamic_cast<const DirectDeclarator*>(declarator_);
    auto identifier = directDecl->getIdentifier();
    context.makeFuncReturnType(declarator_->getId(), declaration_specifiers_);
    std::string temp;

    stream << ".text" << std::endl;
    stream << ".globl ";
    identifier->EmitRISC(stream, context, temp);
    stream << std::endl;

    identifier->EmitRISC(stream, context, temp);
    stream << ":" << std::endl;

    // context.initalizeStack(stream);
    
    declarator_->EmitRISC(stream, context, temp);
    stream << std::endl;

    if (compound_statement_ != nullptr)
    {
        std::string temp;
        compound_statement_->EmitRISC(stream, context, temp);
    }

    // context.restoreRegs(stream);

}

void FunctionDefinition::Print(std::ostream& stream) const
{
    stream << declaration_specifiers_ << " ";

    declarator_->Print(stream);
    stream << "( " << std::endl;
    if (declarator_list_ != nullptr){
        declarator_list_->Print(stream);
    }
    stream << ") {";
    if (compound_statement_ != nullptr)
    {
        compound_statement_->Print(stream);
    }
    stream << "}" << std::endl;
}

}
