#pragma once

#include "../include/ast_node.hpp"

namespace ast {

    class SizeOf : public Node
    {
    private:
        NodePtr expression_;
        TypeSpecifier type_;
        bool isType_;

    public:

        explicit SizeOf(NodePtr expression)
            : expression_(std::move(expression)), type_(TypeSpecifier::INT), isType_(false) {}


        explicit SizeOf(TypeSpecifier type)
            : expression_(nullptr), type_(type), isType_(true) {}

        virtual ~SizeOf()
        {
            if (!isType_ && expression_ != nullptr)
            {
                delete expression_;
            }
        }

        virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;
        virtual void Print(std::ostream &stream) const override;
        virtual EntitySpecifier getEntity() const override;
        virtual TypeSpecifier getType(Context &context) const override;
    };

}


