#pragma once

#include "ast_node.hpp"

namespace ast {
    class Enumerate : public Node {
    private:
        std::string identifier_;
        NodePtr constant_expression_;

    public:
        Enumerate(std::string identifier, NodePtr constant_expression)
            : identifier_(identifier), constant_expression_(std::move(constant_expression)) {}

        virtual ~Enumerate() {
            if (constant_expression_ != nullptr) {
                delete constant_expression_;
            }
        }

        virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;
        virtual TypeSpecifier getType() const;
        virtual std::string getId() const override;
        virtual EntitySpecifier getEntity() const override;
        virtual void Print(std::ostream &stream) const override;
        int getVal() const override;

    };

    class EnumSpecifier : public Node {
    private:
        std::string identifier_;
        NodeList *enumerator_list_;

    public:
        EnumSpecifier(std::string identifier, NodeList *enumerator_list)
            : identifier_(identifier), enumerator_list_(enumerator_list) {}

        virtual ~EnumSpecifier() {
            if (enumerator_list_ != nullptr) {
                delete enumerator_list_;
            }
        }

        virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;
        virtual std::string getId() const override;
        virtual EntitySpecifier getEntity() const override;
        virtual void Print(std::ostream &stream) const override;
        //int getVal() const override;

    };

}
