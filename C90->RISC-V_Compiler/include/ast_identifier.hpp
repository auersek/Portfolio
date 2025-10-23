#pragma once

#include "ast_node.hpp"
#include "ast_enum.hpp"

namespace ast {

class Identifier : public Node
{
private:
    std::string identifier_;

public:
    Identifier(std::string identifier) : identifier_(std::move(identifier)){};

    void EmitRISC(std::ostream& stream, Context& context, std::string &) const override;
    void Print(std::ostream& stream) const override;
    std::string getId() const override { return identifier_; }
    // virtual EntitySpecifier getEntity() const override;
};

} // namespace ast

