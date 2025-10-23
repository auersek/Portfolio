#pragma once

#include "ast_node.hpp"
#include "ast_type_specifier.hpp"

namespace ast {

class InitDeclare : public Node
{
private:
    NodePtr declarator_;
    NodePtr initializer_;

public:
    InitDeclare(NodePtr declarator, NodePtr initalizer)
    : declarator_(declarator),
      initializer_(initalizer) {};

    virtual ~InitDeclare()
    {
        delete declarator_;
        delete initializer_;
    };


    void EmitRISC(std::ostream& stream, Context& context, std::string &) const override;
    void Print(std::ostream& stream) const override;
    virtual std::string getId() const override;
    virtual EntitySpecifier getEntity() const override;
};

class InitDeclareList : public Node
{
private:
    NodeList *in_;

public:
    InitDeclareList(NodeList *first_node)
        : in_(first_node) {};

    virtual ~InitDeclareList() {}

    void EmitRISC(std::ostream& stream, Context& context, std::string &) const override;
    void Print(std::ostream& stream) const override;
    // std::string getId() const override{
    //     return initalizer_->getId();
    // }


};









}
