#include "../include/ast_enum.hpp"

namespace ast {




    void EnumSpecifier::EmitRISC(std::ostream &stream, Context &context, std::string &) const {
        std::string temp;
        context.createEnum(identifier_);
        enumerator_list_->EmitRISC(stream, context,temp);
        context.resEnum();
    }

    void Enumerate::EmitRISC(std::ostream &stream, Context &context, std::string &) const {
        (void)stream;
        if (constant_expression_ != nullptr)
        {
            context.enumAddValue(identifier_, constant_expression_->getVal());
        }
        else
        {
            context.enumAddValue(identifier_, context.setEnumValue());
        }
    }

    TypeSpecifier Enumerate::getType() const {
        return TypeSpecifier::INT;
    }

    std::string Enumerate::getId() const {
        return identifier_;
    }

    EntitySpecifier Enumerate::getEntity() const {
        return EntitySpecifier::ENUMERATOR;
    }

    void Enumerate::Print(std::ostream &stream) const
    {
        std::cout << identifier_ << " : enumerator::print" << std::endl;
        stream << identifier_;
        if (constant_expression_ != nullptr)
        {
            stream << " = ";
            constant_expression_->Print(stream);
        }
    }

    int Enumerate::getVal() const {
        if (constant_expression_ != nullptr) {
            return constant_expression_->getVal();
        }
        throw std::runtime_error("Enumerate: No constant value provided.");
    }


    std::string EnumSpecifier::getId() const {
        return identifier_;
    }

    EntitySpecifier EnumSpecifier::getEntity() const {
        return EntitySpecifier::ENUM_SPECIFIER;
    }

    void EnumSpecifier::Print(std::ostream &stream) const
    {
        stream << "enum " << identifier_ << " {" << std::endl;
        if (enumerator_list_ != nullptr){
            enumerator_list_->Print(stream);
        }
        stream << "}";
    }
}
