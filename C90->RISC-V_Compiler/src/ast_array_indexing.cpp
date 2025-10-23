#include "../include/ast_array_indexing.hpp"
#include "../include/ast_context.hpp"

namespace ast {

    void ArrayIndex::EmitRISC(std::ostream &stream, Context &context, std::string &destReg) const{

        // stream << "DEBUG: var.type = " << static_cast<int>((context.getParam(identifier_->getId())).type) << "\n";

        std::string index_mem = context.getMemLocation(getId());
        std::string index_reg = context.regAlloc();
        index_->EmitRISC(stream, context, index_reg);

        // this assigns memory with respect to the type in arrays
        // multiplied used to assign bytes, e.g. reg = reg x 8

        if (context.getVarType(getId()) == TypeSpecifier::FLOAT){
            stream << "li " << destReg << ", " << TYPE_SIZE_FLOAT << std::endl;
            stream << "mul " << index_reg << ", " << index_reg << ", "
                   << destReg << std::endl;
        }
        else if (context.getVarType(getId()) == TypeSpecifier::DOUBLE){
            stream << "li " << destReg << ", " << TYPE_SIZE_DOUBLE << std::endl;
            stream << "mul " << index_reg << ", " << index_reg << ", "
                   << destReg << std::endl;
        }
        else if (context.getVarType(getId()) == TypeSpecifier::CHAR){
            stream << "li " << destReg << ", " << TYPE_SIZE_CHAR << std::endl;
            stream << "mul " << index_reg << ", " << index_reg << ", "
                   << destReg << std::endl;
        }
        else if (context.getVarType(getId()) == TypeSpecifier::STRING){
            stream << "li " << destReg << ", " << TYPE_SIZE_STRING << std::endl;
            stream << "mul " << index_reg << ", " << index_reg << ", "
                   << destReg << std::endl;
        }
        else{
            stream << "li " << destReg << ", " << TYPE_SIZE_INT << std::endl;
            stream << "mul " << index_reg << ", " << index_reg << ", "
                   << destReg << std::endl;
        }


        stream << "li " << destReg << ", " << index_mem << std::endl;
        stream << "sub " << destReg << ", " << destReg << ", " << index_reg
               << std::endl;
        stream << "add " << destReg << ", " << destReg << ", sp" << std::endl;
        stream << "mv " << index_reg << ", " << destReg << std::endl;
        if (context.getVarType(getId()) == TypeSpecifier::INT)
        {
            stream << "lw " << destReg << ", 0(" << index_reg << ")" << std::endl;
        }
        else if (context.getVarType(getId()) == TypeSpecifier::FLOAT){
            stream << "flw " << destReg << ", 0(" << index_reg << ")" << std::endl;
        }
        else if (context.getVarType(getId()) == TypeSpecifier::DOUBLE){
            stream << "fld " << destReg << ", 0(" << index_reg << ")" << std::endl;
        }
        else if (context.getVarType(getId()) == TypeSpecifier::CHAR){
            stream << "lbu " << destReg << ", 0(" << index_reg << ")" << std::endl;
        }
        else{
            stream << "lw " << destReg << ", 0(" << index_reg << ")" << std::endl;
        }

        if (context.getArrayFlag())
        {
            context.setArrIndex(index_reg);
        }
        else
        {
            context.regDalloc(index_reg);
        }

    }
    void ArrayIndex::Print(std::ostream &stream) const
    {
        identifier_->Print(stream);
        stream << "[";
        index_->Print(stream);
        stream << "]";
    }

    TypeSpecifier ArrayIndex::getType(Context &context) const
    {
        return context.getVarType(identifier_->getId());;
    }
    EntitySpecifier ArrayIndex::getEntity() const
    {
        return EntitySpecifier::ARRAY;
    }

}
