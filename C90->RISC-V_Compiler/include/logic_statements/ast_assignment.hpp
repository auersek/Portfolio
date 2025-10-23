#pragma once

#include "ast_node.hpp"
#include "ast_type_specifier.hpp"
#include <memory>

namespace ast {

class Assignment : public Node
{
private:
    NodePtr     unary_expression_;                 // variable
    std::string assignment_operator_;              // eg "="
    NodePtr     assignment_expression_;            // 1234

public:
    Assignment(NodePtr unary, std::string assignment, NodePtr expr)
        : unary_expression_(std::move(unary)),
          assignment_operator_(assignment),
          assignment_expression_(std::move(expr)) {}
    virtual ~Assignment() = default;

    void EmitRISC(std::ostream& stream, Context& context) const override;
    void Print(std::ostream& stream) const override;

};

}
