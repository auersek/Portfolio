#include "../include/ast_literal.hpp"


namespace ast {



    void StringLiteral::EmitRISC(std::ostream &stream, Context &context, std::string &) const
    {
        std::string pairing = context.labelAlloc("string");
        context.newStringList(pairing, string_literal_);
        std::string tmp = context.regAlloc();

        stream << "lui " << "a" << ", %hi(" << pairing << ")" << std::endl;
        stream << "addi " << tmp << ", " << tmp <<", %lo(" << pairing << ")" << std::endl;
    }

    TypeSpecifier StringLiteral::getType(Context &context) const
    {
        (void)context;
        return TypeSpecifier::STRING;
    }

    EntitySpecifier StringLiteral::getEntity() const
    {
        return EntitySpecifier::STRING_DEFINITION;
    }


    std::string StringLiteral::getId() const
    {
        return string_literal_;
    }

    void StringLiteral::Print(std::ostream &stream) const
    {
        stream << string_literal_;
    }
}
