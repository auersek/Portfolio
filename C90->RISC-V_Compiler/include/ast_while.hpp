#pragma once

#include "ast_node.hpp"

namespace ast {

class WhileStatement : public Node
{
private:
    NodePtr condition_;
    NodePtr statement_;

public:
    WhileStatement(NodePtr cond, NodePtr stat) : condition_(std::move(cond)), statement_(std::move(stat)) {};
    virtual ~WhileStatement()
    {
        delete condition_;
        delete statement_;
    };

    void EmitRISC(std::ostream &stream, Context &context, std::string &) const override;
    void Print(std::ostream &stream) const override;
};

class ForStatement : public Node
{
   private:
    NodePtr expression_statement_;
    NodePtr loop_condition_;
    NodePtr expression_;
    NodePtr statement_;

   public:
    ForStatement(NodePtr expression_statement, NodePtr loop_condition, NodePtr expression, NodePtr statement)
        : expression_statement_(expression_statement),
          loop_condition_(loop_condition),
          expression_(expression),
          statement_(statement)  {};

    virtual ~ForStatement()
    {
        delete expression_statement_;
        delete loop_condition_;
        if (expression_ != nullptr){
            delete expression_;
        }
        delete statement_;
    };

    void EmitRISC(std::ostream &stream, Context &context, std::string &) const override;
    void Print(std::ostream &stream) const override;
};



} // namespace ast




