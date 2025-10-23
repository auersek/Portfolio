#pragma once

#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_node.hpp"

namespace ast {

class Switch : public Node
{

private:
    NodePtr expr_;
    NodeList *list_;

public:
    Switch(NodePtr expr, NodeList *list)
        : expr_(std::move(expr)),
          list_(std::move(list)){};
    virtual ~Switch() = default;

    virtual void EmitRISC(std::ostream &stream,Context &context) const override;
    virtual void EmitRISC(std::ostream &stream,Context &context, std::string destinatonReg) const override;
    virtual void Print(std::ostream &stream) const override;

};




} // ns






