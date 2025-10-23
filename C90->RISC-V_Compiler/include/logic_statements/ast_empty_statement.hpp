#pragma once

#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_node.hpp"

namespace ast {

class emptyStatement : public Node
{
public:
    emptyStatement(){};
    virtual ~emptyStatement() = default;

    virtual void EmitRISC(std::ostream &stream, Context &context) const override;
    virtual void Print(std::ostream &stream) const override;

};

}


