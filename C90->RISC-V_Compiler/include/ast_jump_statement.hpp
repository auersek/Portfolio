#pragma once

#include "ast_node.hpp"

namespace ast {

class ReturnStatement : public Node
{
private:
    NodePtr expression_;

public:
    ReturnStatement(NodePtr expression) : expression_(std::move(expression)) {}
    virtual ~ReturnStatement()
    {
        delete expression_;
    };

    void EmitRISC(std::ostream& stream, Context& context, std::string &) const override;
    void Print(std::ostream& stream) const override;
    // std::string getId() const override{
    //     return expression_;
    // }
};

} // namespace ast
