#include "../include/ast_empty_statement.hpp"
#include <iterator>

void ast::emptyStatement::EmitRISC(std::ostream &stream, Context &context) const {
}

void ast::emptyStatement::Print(std::ostream &stream) const {
    stream << ";";
}

