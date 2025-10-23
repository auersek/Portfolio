#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "ast_direct_declarator.hpp"
#include "ast_function_definition.hpp"
#include "ast_identifier.hpp"
#include "ast_jump_statement.hpp"
#include "ast_node.hpp"
#include "ast_type_specifier.hpp"
#include "ast_constant.hpp"
#include "ast_context.hpp"
#include "ast_while.hpp"
#include "ast_variable.hpp"
#include "ast_if_statement.hpp"
#include "ast_if_else.hpp"
#include "ast_parameter_declare.hpp"
#include "ast_init_declare.hpp"
#include "ast_arithmetic+logical.hpp"
#include "ast_unary.hpp"
#include "ast_compoundassignment.hpp"
#include "ast_assign.hpp"
#include "ast_thans.hpp"
#include "ast_shift.hpp"
#include "ast_equals.hpp"
#include "ast_literal.hpp"
#include "ast_function_call.hpp"
#include "ast_comp_statement.hpp"
#include "ast_postfix.hpp"
#include "ast_prefix.hpp"
#include "ast_sizeof.hpp"
#include "ast_pointers.hpp"
#include "ast_enum.hpp"
#include "ast_array_indexing.hpp"
#include "ast_arrays.hpp"
#include "ast_switch_statement.hpp"
#include "ast_break.hpp"
#include "ast_continue.hpp"


ast::NodePtr ParseAST(std::string file_name);
