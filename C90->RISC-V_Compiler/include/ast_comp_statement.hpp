#include "../include/ast_node.hpp"

namespace ast {

class CompStatement : public Node
{
private:
    NodeList* dec_list_;
    NodeList* stat_list_;

public:
    CompStatement(NodeList* list, NodeList* stat)
        : dec_list_(list),
          stat_list_(stat) {};

    void EmitRISC(std::ostream& stream, Context& context, std::string &destReg) const override;
    void Print(std::ostream& stream) const override;

};

}
