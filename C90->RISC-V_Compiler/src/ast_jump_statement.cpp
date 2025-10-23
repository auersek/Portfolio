#include "/workspaces/langproc-2024-cw-Compile_me_maybe/include/ast_jump_statement.hpp"

namespace ast {

void ReturnStatement::EmitRISC(std::ostream& stream, Context& context, std::string &) const
{
    TypeSpecifier mvType = context.getLastAddedReturnType();

    if (expression_ != nullptr)
    {
        if (mvType == TypeSpecifier::INT || mvType == TypeSpecifier::UNSIGNED){
            std::string temp = context.regAlloc();
            expression_->EmitRISC(stream, context, temp);
            stream << "mv a0, " << temp << std::endl;
            context.endStack(stream);
            context.regDalloc(temp);
            // stream << "#ONCE" << std::endl;
        }
        else if (mvType  == TypeSpecifier::FLOAT){
            std::string temp = context.floatRegAlloc();
            expression_->EmitRISC(stream, context, temp);
            stream << "fmv.s fa0, " << temp << std::endl;
            context.endStack(stream);
            context.floatRegDalloc(temp);
            // stream << "#TWICE" << std::endl;
        }
        else if (mvType  == TypeSpecifier::DOUBLE){
            std::string temp = context.floatRegAlloc();
            expression_->EmitRISC(stream, context, temp);
            stream << "fmv.d fa0, " << temp << std::endl;
            context.endStack(stream);
            context.floatRegDalloc(temp);
            // stream << "#THRICE" << std::endl;
        }
    }
    stream << "jr ra" << std::endl;
}

void ReturnStatement::Print(std::ostream& stream) const
{
    stream << "return";
    if (expression_ != nullptr)
    {
        stream << " ";
        expression_->Print(stream);
    }
    stream << ";" << std::endl;
}

}
