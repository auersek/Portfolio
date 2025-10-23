#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_node.hpp"
#include "ast_type_specifier.hpp"
#include "../include/ast_identifier.hpp"
#include "../include/ast_direct_declarator.hpp"
namespace ast {

class VariableDeclare : public Node
{
private:
    TypeSpecifier var_type_;
    NodePtr var_name_;

public:
    VariableDeclare(TypeSpecifier var_type, NodePtr var_name)
        : var_type_(var_type),
          var_name_(std::move(var_name)){};

    virtual ~VariableDeclare()
    {
        delete var_name_;
    };

    virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;
    virtual void Print(std::ostream &stream) const override;
    std::string getId() const override{
        return var_name_->getId();
    }

    virtual EntitySpecifier getEntity() const override;
};



}
