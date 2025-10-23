// #pragma once

// #include "ast_node.hpp"

// namespace ast {
//     class Conditional : public Node
//     {

//     private:
//     NodePtr logical_or_expression_;
//     NodePtr expression_;
//     NodePtr conditional_expression_;

//     public:

//     Conditional(NodePtr logical_or_expression, NodePtr expression, NodePtr conditional_expression) : logical_or_expression_(std::move(logical_or_expression)), expression_(std::move(expression)), conditional_expression_(std::move(conditional_expression)){}
//     virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;
//     virtual void Print(std::ostream &stream) const override;
//     virtual TypeSpecifier getType(Context &context) const override;

//     };
// }
