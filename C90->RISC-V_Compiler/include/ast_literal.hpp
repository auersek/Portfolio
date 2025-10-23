#pragma once

#include "ast_node.hpp"
#include "ast_type_specifier.hpp"
namespace ast{

    class StringLiteral : public Node
    {
        private:
        std::string string_literal_;

        public:

        StringLiteral(std::string string_literal) : string_literal_(std::move(string_literal)){}

        virtual void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;
        virtual void Print(std::ostream &stream) const override;
        virtual TypeSpecifier getType(Context &context) const override;
        virtual EntitySpecifier getEntity() const override;
        virtual std::string getId() const override;

    };

   class CharLiteral : public Node
    {
    private:
        int char_value_;  // Store as an integer (ASCII)

    public:
        explicit CharLiteral(char char_value) : char_value_(char_value) {}

        void EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const override;
        void Print(std::ostream &stream) const override;
        EntitySpecifier getEntity() const override;
        TypeSpecifier getType(Context &context) const override;
        int getValue() const { return char_value_; }  // Corrected getter
    };
}
