#include "../include/ast_node.hpp"

namespace ast {

class ImmAssign : public Node
{

private:
    NodePtr declarator_;
    NodePtr initializer_;

public:
    ImmAssign(NodePtr declarator, NodePtr initializer)
        : declarator_(declarator),
          initializer_(initializer) {};

    void EmitRISC(std::ostream& stream, Context& context, std::string &destReg) const override;
    void Print(std::ostream& stream) const override;

};

}
