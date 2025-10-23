#include "../include/ast_sizeof.hpp"

namespace ast {

    void SizeOf::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const
    {
        if (isType_) {

            if (type_ == TypeSpecifier::INT) {
                stream << "li " << destReg << ", " << TYPE_SIZE_INT << std::endl;
            }
            else if (type_ == TypeSpecifier::FLOAT) {
                stream << "li " << destReg << ", " << TYPE_SIZE_FLOAT << std::endl;
            }
            else if (type_ == TypeSpecifier::DOUBLE) {
                stream << "li " << destReg << ", " << TYPE_SIZE_DOUBLE << std::endl;
            }
            else if (type_ == TypeSpecifier::CHAR) {
                stream << "li " << destReg << ", " << TYPE_SIZE_CHAR << std::endl;
            }
            else {
                stream << "li " << destReg << ", " << TYPE_SIZE_INT << std::endl;
            }
        }
        else {

            TypeSpecifier exprType = context.getVarType(expression_->getId());

            if (context.getIsPointer(expression_->getId()) && expression_->getEntity() != EntitySpecifier::POINTER_DEREFERENCE) {
                stream << "li " << destReg << ", " << TYPE_SIZE_INT << std::endl;
            }
            else if (exprType == TypeSpecifier::INT) {
                stream << "li " << destReg << ", " << TYPE_SIZE_INT << std::endl;
            }
            else if (exprType == TypeSpecifier::FLOAT) {
                stream << "li " << destReg << ", " << TYPE_SIZE_FLOAT << std::endl;
            }
            else if (exprType == TypeSpecifier::DOUBLE) {
                stream << "li " << destReg << ", " << TYPE_SIZE_DOUBLE << std::endl;
            }
            else if (exprType == TypeSpecifier::CHAR) {
                stream << "li " << destReg << ", " << TYPE_SIZE_CHAR << std::endl;
            }
            else {
                stream << "li " << destReg << ", " << TYPE_SIZE_INT << std::endl;
            }
        }
    }

    void SizeOf::Print(std::ostream &stream) const
    {
        stream << "sizeof(";
        if (isType_) {
            stream << "TYPE";  // Debugging
        }
        else {
            expression_->Print(stream);
        }
        stream << ")";
    }

    EntitySpecifier SizeOf::getEntity() const { return EntitySpecifier::SIZE_OF; }

    TypeSpecifier SizeOf::getType(Context &context) const {
        (void)context;
        return TypeSpecifier::INT;
    }
}
