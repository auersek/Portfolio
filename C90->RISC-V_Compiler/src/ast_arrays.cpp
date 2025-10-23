#include "../include/ast_arrays.hpp"
#include "../include/ast_context.hpp"

namespace ast {

    void ArrayDeclare::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const{
        const Identifier* id_getId = dynamic_cast<const Identifier*>(identifier);
        std::string array_id = id_getId->getId();
        context.newArray(array_id, size->getVal());
        (void) destReg;
        stream << "call " << array_id;
    }
    void ArrayDeclare::Print(std::ostream &stream) const
    {
        identifier->Print(stream);
        stream << "[";
        size->Print(stream);
        stream << "]";
    }


    TypeSpecifier ArrayDeclare::getType(Context &context) const
    {
        return context.getVarType(identifier->getId());;
    }

    EntitySpecifier ArrayDeclare::getEntity() const
    {
        return EntitySpecifier::ARRAY;
    }

}

















