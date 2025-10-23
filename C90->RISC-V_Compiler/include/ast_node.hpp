#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ast_context.hpp"
#include "ast_type_specifier.hpp"

namespace ast {

class Node
{
public:
    virtual ~Node() {}
    virtual void EmitRISC(std::ostream& stream, Context& context, std::string &destReg) const = 0;
    virtual void Print(std::ostream& stream) const = 0;
    virtual std::string getId() const { return {}; };
    virtual TypeSpecifier getType(Context &context) const{
        (void)context;
        return TypeSpecifier::INVALID; };               // use invalid in general
    virtual EntitySpecifier getEntity() const {
        return EntitySpecifier::INVALID;
    }

    virtual int getVal() const {
        throw std::runtime_error("getVal not implemented for this node.");
    }
};

// If you don't feel comfortable using std::unique_ptr, you can switch NodePtr to be defined
// as a raw pointer instead here and your project should still compile, although you'll need
// to add destructors to avoid leaking memory
// (and get rid of the now unnecessary std::move-s)
// using NodePtr = std::unique_ptr<const Node>;

using NodePtr = Node*;

class NodeList : public Node
{
private:
    std::vector<NodePtr> nodes_;

public:
    NodeList() = default;
    NodeList(NodePtr first_node) { nodes_.push_back(std::move(first_node)); }
    virtual ~NodeList() override
    {
        for (auto child : nodes_) {
            delete child;
        }
    }

    void PushBack(NodePtr item);
    virtual void EmitRISC(std::ostream& stream, Context& context, std::string &destReg) const override;
    virtual void Print(std::ostream& stream) const override;
    const std::vector<NodePtr> &getNode() const;


};

} // namespace ast
