#pragma once

#include "ast_node.hpp"

namespace ast{

class Pointers : public Node
{
    private:
    NodePtr nothing_;
   public:
    Pointers(NodePtr nothing)
      : nothing_(nothing) {};
    virtual ~Pointers(){};
    virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;
    virtual void Print(std::ostream &stream) const override;

};

}

namespace ast{
class PointerDeclare : public Node
{
private:
    NodePtr pointer_;
    NodePtr identifier_;

public:

    PointerDeclare(NodePtr pointer, NodePtr identifier)
        : pointer_(pointer),
          identifier_(identifier){};

    virtual ~PointerDeclare(){
        delete pointer_;
        delete identifier_;
    };

    virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;
    virtual void Print(std::ostream &stream) const override;
    std::string getId() const override;
    EntitySpecifier getEntity() const override{
        return EntitySpecifier::POINTER;
    }
    
};
}
