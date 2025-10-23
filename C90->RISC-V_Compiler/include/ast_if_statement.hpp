#pragma once

#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_node.hpp"

namespace ast {

class IfStatement : public Node
{

private:
    NodePtr condition_;
    NodePtr statement_;

public:
    IfStatement(NodePtr cond, NodePtr stat)
        : condition_(std::move(cond)),
          statement_(std::move(stat)) {};
    virtual ~IfStatement()
    {
        delete condition_;
        delete statement_;
    };


    virtual void EmitRISC(std::ostream &stream, Context &context, std::string&) const override;
    virtual void Print(std::ostream &stream) const override;

};

}
