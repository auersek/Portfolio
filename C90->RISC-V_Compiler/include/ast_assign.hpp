#include "../include/ast_node.hpp"
#include "ast_type_specifier.hpp"

namespace ast {

class Assignment : public Node
{
   private:
    NodePtr unary_expression_;
    std::string assignment_operator_;
    NodePtr assignment_expression_;

   public:
    Assignment(NodePtr unary_expression, std::string assignment_operator, NodePtr assignment_expression)
        : unary_expression_(unary_expression),
          assignment_operator_(assignment_operator),
          assignment_expression_(assignment_expression) {}
    virtual ~Assignment()
    {
        delete unary_expression_;
        delete assignment_expression_;
    };

    virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;
    virtual void Print(std::ostream &stream) const override;
    virtual TypeSpecifier getType(Context &context) const override;
};
}
