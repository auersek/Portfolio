#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_parameter_declare.hpp"
#include <cstddef>
#include <string>

namespace ast {

void ParameterDeclare::EmitRISC(std::ostream &stream, Context &context, std::string&) const
{
    // Check
    std::string temp;                   // Not it
    stream << declaration_specifiers_;
    if (declarator_ != nullptr)
    {
        declarator_->EmitRISC(stream, context, temp);
    }
}

void ParameterDeclare::Print(std::ostream &stream) const
{
    stream << declaration_specifiers_ << " ";
    stream << declarator_->getId();
    stream << ", ";

}


void ParameterList::EmitRISC(std::ostream& stream, Context& context, std::string &) const
{
    // (void)context;
    int in = 0;
    int fl = 0;
    for (auto param : getNode()){
        if (param == nullptr){
            continue;
        }

        // stream << "DEBUG: ent.type = " << static_cast<int>(param->getEntity()) << "\n";

        if (param->getEntity() == EntitySpecifier::POINTER) {
            std::string offset = context.takeMemory(TYPE_SIZE_INT);
            context.makeParam(param->getId(), param->getType(context), offset, true);
            stream << "sw a" << in << ", " << offset << "(s0)" << std::endl;
            in++;
        }
        else{
            if (param->getType(context) == TypeSpecifier::INT){
                std::string offset = context.takeMemory(TYPE_SIZE_INT);
                context.makeParam(param->getId(), param->getType(context), offset, false);
                stream << "sw a" << in << ", " << offset << "(s0)" << std::endl;
                in++;
            }
            else if (param->getType(context) == TypeSpecifier::FLOAT) {
                std::string offset = context.takeMemory(TYPE_SIZE_FLOAT);
                context.makeParam(param->getId(), param->getType(context), offset, false);

                stream << "fsw fa" << fl << ", " << offset << "(s0)" << std::endl;
                fl++;
            }
            else if (param->getType(context) == TypeSpecifier::DOUBLE) {
                std::string offset = context.takeMemory(TYPE_SIZE_DOUBLE);
                context.makeParam(param->getId(), param->getType(context), offset, false);
                stream << "fsd fa" << fl << ", " << offset << "(sp)" << std::endl;
                fl++;
            }
        }

    }
}

EntitySpecifier ParameterDeclare::getEntity() const
{
    return declarator_->getEntity();
}


void ParameterList::Print(std::ostream &stream) const
{
    (void)stream;
}

}
