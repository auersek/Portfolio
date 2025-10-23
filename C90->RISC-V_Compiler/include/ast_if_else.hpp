#pragma once

#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_node.hpp"

namespace ast {

class IfElse : public Node
{
private:
    NodePtr condition_;
    NodePtr if_statement_;
    NodePtr else_statement_;

public:
    IfElse(NodePtr cond, NodePtr if_s, NodePtr else_s)
        : condition_(std::move(cond)),
          if_statement_(std::move(if_s)),
          else_statement_(std::move(else_s))  {};
    virtual ~IfElse()
    {
        delete condition_;
        delete if_statement_;
        delete else_statement_;
    };

    virtual void EmitRISC(std::ostream &stream, Context &context, std::string&) const override;
    virtual void Print(std::ostream &stream) const override;

};

}  // name space ast

