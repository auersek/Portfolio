#pragma once

#include "../include/ast_node.hpp"

namespace ast {

    class DirectDeclarator : public Node
    {
    private:
        NodePtr identifier_;
        NodeList* parameter_list_;

    public:
        DirectDeclarator(NodePtr identifier, NodeList* parameter_list)
        : identifier_(std::move(identifier)),
          parameter_list_(parameter_list){};
        virtual ~DirectDeclarator()
        {
            delete identifier_;
            delete parameter_list_;
        };

        void EmitRISC(std::ostream& stream, Context& context, std::string &) const override;
        void Print(std::ostream& stream) const override;
        // std::string getId() const override{
        //     return parameter_list_->getId();
        // }
        virtual std::string getId() const override;
        NodePtr getIdentifier() const {
            return identifier_;
        }

    };

} // namespace ast
