// Adapted from: https://www.lysator.liu.se/c/ANSI-C-grammar-y.html

%code requires {
	#include "ast.hpp"

	using namespace ast;

	extern int yylineno;
	extern char* yytext;
	extern Node* g_root;
	extern FILE* yyin;

	int yylex(void);
	void yyerror(const char*);
	int yylex_destroy(void);
}

%define parse.error detailed
%define parse.lac full

// Represents the value associated with any kind of AST node.
%union {
  Node*        	node;
  NodeList*    	node_list;
  int          	number_int;
  double       	number_float;
  std::string* 	string;
  TypeSpecifier	type_specifier;
  yytokentype  	token;
}

%token IDENTIFIER INT_CONSTANT FLOAT_CONSTANT STRING_LITERAL
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP AND_OP OR_OP
%token MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
%token TYPE_NAME TYPEDEF EXTERN STATIC AUTO REGISTER SIZEOF
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS
%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN
%token UNKNOWN

%type <node> external_declaration function_definition primary_expression postfix_expression
%type <node> unary_expression cast_expression multiplicative_expression additive_expression shift_expression relational_expression
%type <node> equality_expression and_expression exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression
%type <node> conditional_expression assignment_expression expression constant_expression declaration
%type <node> struct_specifier struct_declaration_list struct_declaration struct_declarator_list init_declarator
%type <node> struct_declarator enumerator declarator direct_declarator pointer parameter_declaration
%type <node> identifier_list abstract_declarator direct_abstract_declarator initializer initializer_list statement labeled_statement
%type <node> compound_statement expression_statement selection_statement iteration_statement jump_statement init_declarator_list

%type <node_list> statement_list declaration_list parameter_list argument_expression_list translation_unit enumerator_list

%type <string> unary_operator assignment_operator storage_class_specifier

%type <number_int> INT_CONSTANT
%type <number_float> FLOAT_CONSTANT
%type <string> STRING_LITERAL
%type <string> IDENTIFIER
%type <type_specifier> type_specifier type_name specifier_qualifier_list enum_specifier
// TODO: Make a better type for this (only needed for advanced features)
%type <type_specifier> declaration_specifiers
%type <node> enum_definition

%start ROOT
%%

ROOT
  : translation_unit { g_root = $1; }

translation_unit
	: external_declaration 					        { $$ = new NodeList($1); 		}
	| translation_unit external_declaration       	{ $1->PushBack($2); $$ = $1; 	}
	;

external_declaration
	: function_definition 	{ $$ = $1; }
	| declaration		 	{ $$ = $1; }
    | enum_definition       { $$ = $1; }
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement     { $$ = new FunctionDefinition($1, $2, $3, $4);      				}
	| declaration_specifiers declarator compound_statement 						{ $$ = new FunctionDefinition($1, $2, nullptr, $3); 				}
	| declarator declaration_list compound_statement							{ $$ = new FunctionDefinition(TypeSpecifier::INT, $1, $2, $3); 		}
	| declarator compound_statement												{ $$ = new FunctionDefinition(TypeSpecifier::INT, $1, nullptr, $2); }
	;
	// changed bottom two funcDef but I don't think they are ever needed

primary_expression
	: IDENTIFIER {
        std::cout << "# DEBUG: primary_expression is an IDENTIFIER: " << *$1 << std::endl;
        $$ = new Identifier(*$1);
        delete $1;
    }
	| INT_CONSTANT {
        std::cout << "# DEBUG: primary_expression is an INT_CONSTANT: " << $1 << std::endl;
        $$ = new IntConstant($1);
    }
    | FLOAT_CONSTANT {
        std::cout << "# DEBUG: primary_expression is a FLOAT_CONSTANT: " << $1 << std::endl;
        $$ = new FloatConstant($1);
    }
	| STRING_LITERAL        { $$ = new StringLiteral(*$1); delete $1; }
	| '(' expression ')' { $$ = $2; }
	;

postfix_expression
	: primary_expression									{ $$ = $1; 								}
	| postfix_expression '[' expression ']'                 { $$ = new ArrayIndex($1, $3);          }
	| postfix_expression '(' ')'							{ $$ = new FunctionCall($1, nullptr); 	}
	| postfix_expression '(' argument_expression_list ')'	{ $$ = new FunctionCall($1, $3); 	  	}
	| postfix_expression '.' IDENTIFIER
	| postfix_expression PTR_OP IDENTIFIER
	| postfix_expression INC_OP 							{ $$ = new Postfixer($1, "++"); }
	| postfix_expression DEC_OP 							{ $$ = new Postfixer($1, "--"); }
	;

argument_expression_list
	: assignment_expression									{ $$ = new ParameterList($1); }
	| argument_expression_list ',' assignment_expression	{ $$ = $1; $1->PushBack($3);  }
	;



unary_expression
	: postfix_expression									{ $$ = $1;								}
	| INC_OP unary_expression 								{ $$ = new Prefixer($2, "++"); 			}
	| DEC_OP unary_expression 								{ $$ = new Prefixer($2, "--"); 			}
	| unary_operator cast_expression						{ $$ = new Unary(*$1, $2); delete $1;	}
	| SIZEOF unary_expression 								{ $$ = new SizeOf($2); 					}
	| SIZEOF '(' type_name ')' 								{ $$ = new SizeOf($3); 					}
	;



unary_operator
	: '&'		{ $$ = new std::string("&"); }
	| '*'		{ $$ = new std::string("*"); }
	| '+'		{ $$ = new std::string("+"); }
	| '-'		{ $$ = new std::string("-"); }
	| '~'		{ $$ = new std::string("~"); }
	| '!'		{ $$ = new std::string("!"); }
	;

cast_expression
	: unary_expression						{ $$ = $1; }
	| '(' type_name ')' cast_expression
	;

multiplicative_expression
	: cast_expression								{ $$ = $1; 				  }
	| multiplicative_expression '*' cast_expression { $$ = new MulOp($1, $3); }
	| multiplicative_expression '/' cast_expression { $$ = new DivOp($1, $3); }
	| multiplicative_expression '%' cast_expression { $$ = new ModOp($1, $3); }
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression { $$ = new AddOp($1, $3); }
	| additive_expression '-' multiplicative_expression { $$ = new SubOp($1, $3); }
	;


shift_expression
	: additive_expression
	| shift_expression LEFT_OP additive_expression 	{ $$ = new LeftShift($1, $3); 	}
	| shift_expression RIGHT_OP additive_expression { $$ = new RightShift($1, $3); 	}
	;

relational_expression
	: shift_expression
	| relational_expression '<' shift_expression	{ $$ = new LessThan($1, $3); 			}
	| relational_expression '>' shift_expression 	{ $$ = new GreaterThan($1, $3); 		}
	| relational_expression LE_OP shift_expression 	{ $$ = new LessThanEqual($1, $3); 		}
	| relational_expression GE_OP shift_expression 	{ $$ = new GreaterThanEqual($1, $3); 	}
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP relational_expression { $$ = new IsEqual($1, $3);       }
	| equality_expression NE_OP relational_expression { $$ = new IsNotEqual($1, $3);    }
	;

and_expression
	: equality_expression
	| and_expression '&' equality_expression { $$ = new BitAndOp($1, $3); }
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression '^' and_expression { $$ = new BitXorOp($1, $3); }
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression '|' exclusive_or_expression { $$ = new BitOrOp($1, $3); }
	;

logical_and_expression
	: inclusive_or_expression
	| logical_and_expression AND_OP inclusive_or_expression { $$ = new LogAndOp($1, $3); }
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression OR_OP logical_and_expression { $$ = new LogOrOp($1, $3); }
	;


conditional_expression
	: logical_or_expression
	| logical_or_expression '?' expression ':' conditional_expression
	;

assignment_expression
    : conditional_expression {
        std::cout << "# DEBUG: assignment_expression is a conditional_expression" << std::endl;
        $$ = $1;
    }
    | unary_expression assignment_operator assignment_expression {
        std::cout << "# DEBUG: assignment_expression contains an assignment" << std::endl;
        $$ = new Assignment($1, *$2, $3);
        delete $2;
    }
    ;

	// x = y, x = y+20

assignment_operator
	: '='				{ $$ = new std::string("="); 	}
	| MUL_ASSIGN		{ $$ = new std::string("*="); 	}
	| DIV_ASSIGN		{ $$ = new std::string("/="); 	}
	| MOD_ASSIGN		{ $$ = new std::string("%="); 	}
	| ADD_ASSIGN		{ $$ = new std::string("+="); 	}
	| SUB_ASSIGN		{ $$ = new std::string("-="); 	}
	| LEFT_ASSIGN		{ $$ = new std::string("<<="); 	}
	| RIGHT_ASSIGN		{ $$ = new std::string(">>="); 	}
	| AND_ASSIGN		{ $$ = new std::string("&="); 	}
	| XOR_ASSIGN		{ $$ = new std::string("^="); 	}
	| OR_ASSIGN			{ $$ = new std::string("|="); 	}
	;


expression
	: assignment_expression
	| expression ',' assignment_expression
	;

constant_expression
	: conditional_expression
	;

		/* new VariableDeclare($1, nullptr) */
        // new VariableDeclare($1, nullptr);

declaration
	: declaration_specifiers ';'						{ $$ = new VariableDeclare($1, nullptr);    }
	| declaration_specifiers init_declarator_list ';'  	{ $$ = new VariableDeclare($1, $2);         }
	;

declaration_specifiers
	: storage_class_specifier
	| storage_class_specifier declaration_specifiers
	| type_specifier 									{ $$ = $1; }
	| type_specifier declaration_specifiers
	;


init_declarator_list
	: init_declarator							{ $$ = $1; }
	/* | init_declarator_list ',' init_declarator	{ $$ = $1; $1->PushBack($3); 	} */
	;

	// { $$ = new NodeList($1); 	 } { $$ = new InitDeclare($1, nullptr); }
 	/* { $1->PushBack($3); $$ = $1; } */
	//
	// { $$ = new InitDeclare($1, $3); 	 	}

init_declarator
	: declarator					{ $$ = new InitDeclare($1, nullptr); 	}		                                //$$ = new ImmAssign($1, nullptr);      // used to be
	| declarator '=' initializer	{ $$ = new InitDeclare($1, $3); 		}													// $$ = new ImmAssign($1, $3);
	;


storage_class_specifier
	: TYPEDEF
	| EXTERN
	| STATIC
	| AUTO
	| REGISTER
	;

type_specifier
	: VOID				{ $$ = TypeSpecifier::VOID; 		}
	| CHAR				{ $$ = TypeSpecifier::CHAR; 		}
	| SHORT				{ $$ = TypeSpecifier::SHORT; 		}
	| INT 				{ $$ = TypeSpecifier::INT; 			}
	| LONG				{ $$ = TypeSpecifier::LONG; 		}
	| FLOAT				{ $$ = TypeSpecifier::FLOAT; 		}
	| DOUBLE			{ $$ = TypeSpecifier::DOUBLE; 		}
	| SIGNED			{ $$ = TypeSpecifier::SIGNED; 		}
	| UNSIGNED			{ $$ = TypeSpecifier::UNSIGNED; 	}
  | struct_specifier
	| enum_specifier    { $$ = TypeSpecifier::ENUM;         }
	| TYPE_NAME
	;

struct_specifier
	: STRUCT IDENTIFIER '{' struct_declaration_list '}'
	| STRUCT '{' struct_declaration_list '}'
	| STRUCT IDENTIFIER
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' struct_declarator
	;

struct_declarator
	: declarator
	| ':' constant_expression
	| declarator ':' constant_expression
	;

enum_definition
	: ENUM '{' enumerator_list '}'              { $$ = new EnumSpecifier("", $3); }
	| ENUM IDENTIFIER '{' enumerator_list '}'   { $$ = new EnumSpecifier(*$2, $4); delete $2; }
	| ENUM IDENTIFIER                           { $$ = new EnumSpecifier(*$2, nullptr); delete $2; }
;
enum_specifier
	: ENUM '{' enumerator_list '}'              { $$ = TypeSpecifier::ENUM; }
	| ENUM IDENTIFIER '{' enumerator_list '}'   { $$ = TypeSpecifier::ENUM; delete $2; }
	| ENUM IDENTIFIER                           { $$ = TypeSpecifier::ENUM; delete $2; }
	;

enumerator_list
	: enumerator                                { $$ = new NodeList($1); }
	| enumerator_list ',' enumerator            { $1->PushBack($3); $$ = $1; }
	;

enumerator
	: IDENTIFIER                                { $$ = new Enumerate(*$1, nullptr); delete $1; }
	| IDENTIFIER '=' constant_expression        { $$ = new Enumerate(*$1, $3); delete $1; }
	;

declarator
	: pointer direct_declarator     { $$ = new PointerDeclare($1, $2);}
	| direct_declarator 			{ $$ = $1; }
	;

direct_declarator
	: IDENTIFIER    									{ $$ = new Identifier(*$1); delete $1;      }
	| '(' declarator ')'
	| direct_declarator '[' constant_expression ']'     { $$ = new ArrayDeclare($1, $3);              }
	| direct_declarator '[' ']'
	| direct_declarator '(' parameter_list ')'			{ $$ = new DirectDeclarator($1, $3);        }
	| direct_declarator '(' identifier_list ')'
	| direct_declarator '(' ')' 						{ $$ = new DirectDeclarator($1, nullptr);   }
	;
	// changed last one from nullptr to parameterList

pointer
	: '*'				{ $$ = new Pointers(nullptr);}
	| '*' pointer
	;


parameter_list
	: parameter_declaration                         { $$ = new ParameterList($1);	}
	| parameter_list ',' parameter_declaration      { $$ = $1; $1->PushBack($3);    }
	;

parameter_declaration
	: declaration_specifiers declarator                 { $$ = new ParameterDeclare($1, $2); 		}
	| declaration_specifiers abstract_declarator		{ $$ = new ParameterDeclare($1, nullptr); 	}
	| declaration_specifiers
	;

identifier_list
	: IDENTIFIER
	| identifier_list ',' IDENTIFIER
	;

type_name
	: specifier_qualifier_list {$$ = $1; }
	/*| specifier_qualifier_list abstract_declarator*/
	;

abstract_declarator
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'
	| '[' ']'
	| '[' constant_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' constant_expression ']'
	| '(' ')'
	| '(' parameter_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_list ')'
	;

initializer
	: assignment_expression			{ $$ = $1; }
	| '{' initializer_list '}'		{ $$ = $2; }
	| '{' initializer_list ',' '}'	{ $$ = $2; }
	;




initializer_list
	: initializer						{ $$ = new NodeList($1); }
	| initializer_list ',' initializer	{ static_cast<NodeList*>($1)->PushBack(NodePtr($3)); $$ = $1;}
	;

statement
	: labeled_statement			{ $$ = $1; }
	| compound_statement		{ $$ = $1; }
	| expression_statement		{ $$ = $1; }
	| selection_statement		{ $$ = $1; }
	| iteration_statement		{ $$ = $1; }
	| jump_statement 			{ $$ = $1; }
	;

labeled_statement
	: IDENTIFIER ':' statement
	| CASE constant_expression ':' statement
	| DEFAULT ':' statement
	;

		// TODO: correct this
compound_statement
	: '{' '}' 									{ $$ = nullptr; 				  }
	| '{' statement_list '}' 					{ $$ = $2;                        }
	| '{' declaration_list '}' 				 	{ $$ = $2;                        }
	| '{' declaration_list statement_list '}'   { $$ = new CompStatement($2, $3); }
	;



declaration_list
	: declaration								{ $$ = new NodeList($1); 	}
	| declaration_list declaration				{ $1->PushBack($2); $$= $1; }
	;

statement_list
	: statement 							{ $$ = new NodeList($1); 	}
	| statement_list statement 				{ $1->PushBack($2); $$= $1; }
	;

expression_statement
	: ';'
	| expression ';' { $$ = $1; }
	;

selection_statement
	: IF '(' expression ')' statement					{ $$ = new IfStatement($3, $5);     }
	| IF '(' expression ')' statement ELSE statement	{ $$ = new IfElse($3, $5, $7);      }
	| SWITCH '(' expression ')' statement
	;

iteration_statement
	: WHILE '(' expression ')' statement										    { $$ = new WhileStatement($3, $5);       }
	| DO statement WHILE '(' expression ')' ';'
	| FOR '(' expression_statement expression_statement ')' statement
	| FOR '(' expression_statement expression_statement expression ')' statement    { $$ = new ForStatement($3, $4, $5, $7); }
	;

jump_statement
	: GOTO IDENTIFIER ';'
	| CONTINUE ';'           { $$ = new ContinueStatement();        }
	| BREAK ';'              { $$ = new BreakKeyWord();             }
	| RETURN ';'			 { $$ = new ReturnStatement(nullptr);   }
	| RETURN expression ';'  { $$ = new ReturnStatement($2);        }
	;

%%

void yyerror (const char *s)
{
  std::cerr << "Error: " << s << " at line " << yylineno;
  std::cerr << " near '" << yytext << "'" << std::endl;
  std::exit(1);
}

Node* g_root;

NodePtr ParseAST(std::string file_name)
{
  yyin = fopen(file_name.c_str(), "r");
  if (yyin == nullptr) {
    std::cerr << "Couldn't open input file: " << file_name << std::endl;
    std::exit(1);
  }

  g_root = nullptr;
  yyparse();

  fclose(yyin);
  yylex_destroy();

  return NodePtr(g_root);
}
