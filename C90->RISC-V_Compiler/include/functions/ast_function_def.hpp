#pragma once

#include "/workspaces/aurelersek/Desktop/langproc-cw-main/include/ast_node.hpp"
#include "/workspaces/aurelersek/Desktop/langproc-cw-main/include/ast_type_specifier.hpp"
#include <ostream>


namespace ast {

class FunctionDef : public Node
{
private:
    const TypeSpecifier specifiers_;
    NodePtr func_;
    NodePtr statement_;

public:
    FunctionDef(TypeSpecifier declaration_specifiers, NodePtr declarator, NodePtr compound_statement) : specifiers_(declaration_specifiers), func_(std::move(declarator)), statement_(std::move(compound_statement)){};
    virtual ~FunctionDef() = default;

    virtual void EmitRISC(std::ostream& stream, Context& context) const override;
    virtual void Print(std::ostream& stream) const override;
};

} // name space ast
