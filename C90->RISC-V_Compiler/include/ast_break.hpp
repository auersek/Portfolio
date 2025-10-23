#pragma once

#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_node.hpp"

namespace ast {

class BreakKeyWord : public Node
{

public:
    BreakKeyWord(){};
    virtual ~BreakKeyWord() = default;
    virtual void EmitRISC(std::ostream &stream, Context &context, std::string &) const override;
    virtual void Print(std::ostream &stream) const override;
};

}
