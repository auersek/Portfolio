#pragma once

#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_node.hpp"

#include <algorithm>
#include <ostream>
#include "ast_identifier.hpp"
namespace ast {

class FunctionCall : public Node
{

private:
    NodePtr func_name_;
    NodeList* parameters_names_;

public:
    FunctionCall(NodePtr func_name, NodeList* parameters_names)
        : func_name_(std::move(func_name)),
          parameters_names_(parameters_names) {};

    virtual ~FunctionCall()
    {
        delete func_name_;
        if (parameters_names_ != nullptr)
        {
            delete parameters_names_;
        }
    };

    virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;
    virtual void Print(std::ostream &stream) const override;
    std::string getId() {
        return func_name_->getId();
    }
};


} // name space




