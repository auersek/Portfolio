#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_node.hpp"

namespace ast {

void NodeList::PushBack(NodePtr item)
{
    nodes_.push_back(std::move(item));
}

void NodeList::EmitRISC(std::ostream& stream, Context& context, std::string &destReg) const
{
    for (const auto& node : nodes_)
    {
        if (node == nullptr)
        {
            continue;
        }
        // std::string temp;
        node->EmitRISC(stream, context, destReg);
    }
}

void NodeList::Print(std::ostream& stream) const
{
    for (const auto& node : nodes_)
    {
        if (node == nullptr)
        {
            continue;
        }
        node->Print(stream);
    }
}

const std::vector<NodePtr>& NodeList::getNode() const {
    return nodes_;
}

}
