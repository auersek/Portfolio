#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_init_declare.hpp"
#include <cstddef>
#include <string>

namespace ast {

void InitDeclare::EmitRISC(std::ostream &stream, Context &context, std::string &) const
{
    Variables var = context.getVariable(declarator_->getId());
    std::string offset = context.getMemLocation(declarator_->getId());
    std::string temp;
    if (initializer_) {
        if (var.PointerOrNot){
            std::string reg = context.regAlloc();
            initializer_->EmitRISC(stream, context, reg);
            stream << "sw " << reg << ", " << offset << "(s0)" << std::endl;
            context.regDalloc(reg);
        }
        else if (var.type == TypeSpecifier::INT)
            {
                std::string reg = context.regAlloc();
                initializer_->EmitRISC(stream, context, reg);
                stream << "sw " << reg << ", " << offset << "(s0)" << std::endl;
                context.regDalloc(reg);
            }
        else if (var.type == TypeSpecifier::FLOAT)
            {
                std::string regf = context.floatRegAlloc();
                initializer_->EmitRISC(stream, context, regf);
                stream << "fsw " << regf << ", " << offset << "(s0)" << std::endl;
                context.floatRegDalloc(regf);
            }
        else if (var.type == TypeSpecifier::DOUBLE)
            {
                std::string regf = context.floatRegAlloc();
                initializer_->EmitRISC(stream, context, regf);
                stream << "fsd " << regf << ", " << offset << "(sp)" << std::endl;
                context.floatRegDalloc(regf);
            }

        else {
                std::string temp;
                initializer_->EmitRISC(stream, context, temp);
            }
    }

}

void InitDeclareList::EmitRISC(std::ostream &stream, Context &context, std::string &) const
{
    for (auto node : in_->getNode()){
        std::string temp;
        if(in_ == nullptr){
            continue;
        }
        // (void)node;
        node->EmitRISC(stream, context, temp);
    }

}

EntitySpecifier InitDeclare::getEntity() const { return declarator_->getEntity(); }

std::string InitDeclare::getId() const { return declarator_->getId(); }

void InitDeclare::Print(std::ostream &stream) const {
    (void)stream;
}

void InitDeclareList::Print(std::ostream &stream) const {
    (void)stream;
}

}



