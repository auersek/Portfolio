#pragma once

#include "ast_context.hpp"
#include "ast_node.hpp"
#include "ast_type_specifier.hpp"

namespace ast {

class ParameterDeclare : public Node
{
private:
    const TypeSpecifier declaration_specifiers_;
    NodePtr declarator_;

public:
    ParameterDeclare(TypeSpecifier declaration_specifiers, NodePtr declarator)
    : declaration_specifiers_(declaration_specifiers),
      declarator_(std::move(declarator)) {};

    void EmitRISC(std::ostream& stream, Context& context, std::string &) const override;
    void Print(std::ostream& stream) const override;
    TypeSpecifier getType(Context &context) const override {
        (void)context;
        return declaration_specifiers_;
    }
    std::string getId() const override{
        return declarator_->getId();
    }
    virtual EntitySpecifier getEntity() const override;
};

class ParameterList : public NodeList
{

public:
    using NodeList::NodeList;

    virtual ~ParameterList() {};

    virtual void EmitRISC(std::ostream &stream, Context &context, std::string &) const override;
    virtual void Print(std::ostream &stream) const override;

};


}

