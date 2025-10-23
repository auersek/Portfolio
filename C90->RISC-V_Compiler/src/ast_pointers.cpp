#include "../include/ast_pointers.hpp"


namespace ast {

    void Pointers::EmitRISC(std::ostream& stream, Context& context, std::string &destReg) const
    {
        (void) stream;
        (void) context;
        (void) destReg;
    }

    void Pointers::Print(std::ostream& stream) const
    {
        stream << "My name is";
    }

    void PointerDeclare::EmitRISC(std::ostream& stream, Context& context, std::string &destReg) const
    {
        // std::string tmp;
        // stream << "DEBUG: " << identifier_->getId();
        // context.allocateStackSpace(identifier_->getId(), TypeSpecifier::INVALID, true);
        // context.makePointer(identifier_->getId());
        // std::cout << "MADE A POINTER";
        identifier_->EmitRISC(stream, context, destReg);    // might be destReg
        (void) destReg;
    }

    void PointerDeclare::Print(std::ostream& stream) const
    {
        std::cout << "printing pointer declare" << std::endl;
        pointer_->Print(stream);
        identifier_->Print(stream);
    }

    std::string PointerDeclare::getId() const {
        return identifier_->getId();
    }


}



