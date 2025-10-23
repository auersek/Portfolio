#include "../include/ast_continue.hpp"

namespace ast {


void ContinueStatement::EmitRISC(std::ostream &stream, Context &context, std::string&) const {

    stream << "j " << context.loopConditionLabel() << std::endl;             // Im not sure, I think loop condition is the right one

}

void ast::ContinueStatement::Print(std::ostream &stream) const {
    stream << "continue;" << std::endl;

}

}


