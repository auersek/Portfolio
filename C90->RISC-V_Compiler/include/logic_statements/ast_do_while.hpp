#pragma once

#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_node.hpp"

namespace ast {

class DoWhile : public Node{

private:
    NodePtr statement_;
    NodePtr condition_;

public:
    DoWhile(NodePtr stat, NodePtr cond)
        : statement_(std::move(stat)),
          condition_(std::move(cond)) {};
    virtual ~DoWhile() = default;

    virtual void EmitRISC(std::ostream &stream, Context &context) const override;
    virtual void Print(std::ostream &stream) const override;
};

}




