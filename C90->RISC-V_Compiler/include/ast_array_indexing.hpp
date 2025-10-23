#pragma once
#include "../include/ast_node.hpp"

namespace ast {

class ArrayIndex : public Node
{
   private:
    NodePtr identifier_;
    NodePtr index_;

   public:
    ArrayIndex(NodePtr identifier, NodePtr index)
        : identifier_(identifier), index_(index){};
    virtual ~ArrayIndex()
    {
        delete identifier_;
        delete index_;
    };
    virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;
    virtual void Print(std::ostream &stream) const override;
    virtual TypeSpecifier getType(Context &context) const override;
    virtual EntitySpecifier getEntity() const override;
    std::string getId() const override{
        return identifier_->getId();
    }
};
}
