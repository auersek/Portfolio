#pragma once

#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_node.hpp"

namespace ast {

class enum_spec : public Node
{

private:
    std::string enum_name_;
    NodeList *expr_;

public:
    enum_spec(std::string enum_name, NodeList *expr)
        : enum_name_(std::move(enum_name)),
          expr_(std::move(expr)) {};
    virtual ~enum_spec() = default;

private:
    virtual void EmitRISC(std::ostream &stream, Context &context) const override;
    virtual void Print(std::ostream &stream) const override;
};

} // namespace

