#pragma once

#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_node.hpp"
#include <ostream>

namespace ast{

class ContinueStatement : public Node
{

public:
    ContinueStatement(){};
    virtual ~ContinueStatement() = default;
    virtual void EmitRISC(std::ostream &stream, Context &context, std::string&) const override;
    virtual void Print(std::ostream &stream) const override;
};

} // namespace ast

