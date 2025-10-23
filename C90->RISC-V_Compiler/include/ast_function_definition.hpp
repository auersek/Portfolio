#pragma once

#include "ast_node.hpp"
#include "ast_type_specifier.hpp"
#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_direct_declarator.hpp"

namespace ast {

class FunctionDefinition : public Node
{
private:
    const TypeSpecifier declaration_specifiers_;
    NodePtr declarator_;
    NodePtr declarator_list_;
    NodePtr compound_statement_;

public:
    FunctionDefinition(TypeSpecifier declaration_specifiers, NodePtr declarator, NodePtr declarator_list, NodePtr compound_statement)
    : declaration_specifiers_(declaration_specifiers),
      declarator_(std::move(declarator)),
      declarator_list_(std::move(declarator_list)),
      compound_statement_(std::move(compound_statement)){};
    virtual ~FunctionDefinition()
    {
        delete declarator_;
        delete declarator_list_;
        delete compound_statement_;
    };
    void EmitRISC(std::ostream& stream, Context& context, std::string &) const override;
    void Print(std::ostream& stream) const override;
    std::string getId() const override{
        return declarator_list_->getId();
    }
};

} // namespace ast
