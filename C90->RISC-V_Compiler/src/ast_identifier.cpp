#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_identifier.hpp"
#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_type_specifier.hpp"



namespace ast {


void Identifier::EmitRISC(std::ostream& stream, Context &context, std::string &destReg) const {
    // EntitySpecifier ent_type = context.getEntity(identifier_);

    if (context.parameters.find(identifier_) != context.parameters.end()){          // for parameters
        Parameters param = context.getParam(identifier_);
        // stream << "DEBUG: var.type = " << static_cast<int>(param.type) << "\n";
        // if (param.memLocation != ""){
        if (param.PointerOrNot){
            std::string offset = context.getMemLocation(identifier_);
            stream << "lw " << destReg << ", " << offset << "(s0)\n";
            // context.regDalloc(destReg);
        }
        else {
            switch (param.type) {
                case TypeSpecifier::INT: {
                    std::string offset = context.getMemLocation(identifier_);
                    stream << "lw " << destReg << ", " << offset << "(s0)\n";
                    // context.regDalloc(destReg);
                    break;
                }
                case TypeSpecifier::FLOAT: {
                    std::string offset = context.getMemLocation(identifier_);
                    stream << "flw " << destReg << ", " << offset << "(s0)\n";
                    // context.floatRegDalloc(destReg);
                    break;
                }
                case TypeSpecifier::CHAR: {
                    std::string offset = context.getMemLocation(identifier_);
                    stream << "lb " << destReg << ", " << offset << "(s0)\n";
                    // context.regDalloc(destReg);
                    break;
                }
                case TypeSpecifier::BOOL: {
                    std::string offset = context.getMemLocation(identifier_);
                    stream << "lb " << destReg << ", " << offset << "(s0)\n";
                    // context.regDalloc(destReg);
                    break;
                }
                case TypeSpecifier::DOUBLE: {
                    std::string offset = context.getMemLocation(identifier_);
                    stream << "fld " << destReg << ", " << offset << "(sp)\n";
                    // context.floatRegDalloc(destReg);
                    break;
                }
                default:
                    stream << "";
            }
        }
    }
    else if (context.LocalVariables.find(identifier_) != context.LocalVariables.end()){      // for local vars
        Variables var = context.getVariable(identifier_);
        // stream << "DEBUG: identifier_ = " << identifier_ << "\n";
        // stream << "DEBUG: ent_type = " << static_cast<int>(ent_type) << "\n";
        // stream << "DEBUG: var.type = " << static_cast<int>(var.type) << "\n";
        // stream << "DEBUG: var.offset = " << var.memLocation << "\n";
        // if (var.memLocation != ""){
        if (var.PointerOrNot){
                std::string offset = context.getMemLocation(identifier_);
                stream << "lw " << destReg << ", " << offset << "(s0)\n";
                // context.regDalloc(destReg);
            }
        else {
            switch (var.type) {
                case TypeSpecifier::INT: {
                    std::string offset = context.getMemLocation(identifier_);
                    stream << "lw " << destReg << ", " << offset << "(s0)\n";
                    // context.regDalloc(destReg);
                    break;
                }

                case TypeSpecifier::FLOAT: {
                    std::string offset = context.getMemLocation(identifier_);
                    stream << "flw " << destReg << ", " << offset << "(s0)\n";
                    // context.floatRegDalloc(destReg);
                    break;
                }

                case TypeSpecifier::CHAR: {
                    std::string offset = context.getMemLocation(identifier_);
                    stream << "lb " << destReg << ", " << offset << "(s0)\n";
                    // context.regDalloc(destReg);
                    break;
                }

                case TypeSpecifier::BOOL: {
                    std::string offset = context.getMemLocation(identifier_);
                    stream << "lb " << destReg << ", " << offset << "(s0)\n";
                    // context.regDalloc(destReg);
                    break;
                }

                case TypeSpecifier::DOUBLE: {
                    std::string offset = context.getMemLocation(identifier_);
                    stream << "fld " << destReg << ", " << offset << "(sp)\n";
                    // context.floatRegDalloc(destReg);
                    break;
                }
                default:
                stream << "";                 //lw " << destReg << ", " << context.getMemLocation(identifier_) << "(sp)" << std::endl;
            }
        }
    }
    else {
        try {
            int enum_val = context.lookupEnumValue(identifier_);
            stream << "li " << destReg << ", " << enum_val << "\n";
            context.regDalloc(destReg);
            return;
        } catch (const std::runtime_error&) {
        }
        // stream << context.printEnumNames();
        // if (!context.isEnumVal(identifier_)){
        // if (identifier_ != "vv"){
            stream << identifier_;
        // }
        // }
    }
}


// EntitySpecifier Identifier::getEntity() const
// {
//     return EntitySpecifier::VARIABLE;
// }


void Identifier::Print(std::ostream& stream) const
{
    stream << identifier_;

};

}
