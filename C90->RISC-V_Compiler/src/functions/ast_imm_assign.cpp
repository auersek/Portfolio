#include "../include/ast_imm_assign.hpp"


namespace ast{


    void ImmAssign::EmitRISC(std::ostream &stream, Context &context, std::string&) const {
        // stream << "#HELLLO";
        std::string temp;
        if (context.parameters.find(declarator_->getId()) != context.parameters.end()){          // for parameters
            Parameters param = context.getParam(declarator_->getId());
            if (param.type == TypeSpecifier::INT)
            {
                temp = context.regAlloc();
                std::string offset = context.getMemLocation(declarator_->getId());
                initializer_->EmitRISC( stream, context, temp);
                stream << "sw " << temp << ", " << offset << "(sp)" << std::endl;
                context.regDalloc(temp);
            }
        }

        if (context.LocalVariables.find(declarator_->getId()) != context.LocalVariables.end()){          // for vars
            Variables var = context.getVariable(declarator_->getId());
            if (var.type == TypeSpecifier::INT)
            {
                temp = context.regAlloc();
                std::string offset = context.getMemLocation(declarator_->getId());
                initializer_->EmitRISC( stream, context, temp);
                stream << "sw " << temp << ", " << offset << "(sp)" << std::endl;
                context.regDalloc(temp);
            }
        }
    }

    void ImmAssign::Print(std::ostream& stream) const {
        (void)stream;
    }

}
