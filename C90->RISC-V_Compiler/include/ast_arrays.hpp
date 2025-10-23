#pragma once
#include "../include/ast_node.hpp"
#include "../include/ast_identifier.hpp"

namespace ast {

class ArrayDeclare : public Node
{
   private:
    NodePtr identifier;
    NodePtr size;

   public:
    ArrayDeclare(NodePtr identifier, NodePtr size)
        : identifier(identifier), size(size){};
    virtual ~ArrayDeclare()
    {
        delete identifier;
        delete size;
    };
    virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;
    virtual void Print(std::ostream &stream) const override;
    virtual TypeSpecifier getType(Context &context) const override;
    virtual EntitySpecifier getEntity() const override;
    std::string getId() const override{
        return identifier->getId();
    }
};
}
