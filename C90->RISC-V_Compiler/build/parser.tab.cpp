/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1





# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_INT_CONSTANT = 4,               /* INT_CONSTANT  */
  YYSYMBOL_FLOAT_CONSTANT = 5,             /* FLOAT_CONSTANT  */
  YYSYMBOL_STRING_LITERAL = 6,             /* STRING_LITERAL  */
  YYSYMBOL_PTR_OP = 7,                     /* PTR_OP  */
  YYSYMBOL_INC_OP = 8,                     /* INC_OP  */
  YYSYMBOL_DEC_OP = 9,                     /* DEC_OP  */
  YYSYMBOL_LEFT_OP = 10,                   /* LEFT_OP  */
  YYSYMBOL_RIGHT_OP = 11,                  /* RIGHT_OP  */
  YYSYMBOL_LE_OP = 12,                     /* LE_OP  */
  YYSYMBOL_GE_OP = 13,                     /* GE_OP  */
  YYSYMBOL_EQ_OP = 14,                     /* EQ_OP  */
  YYSYMBOL_NE_OP = 15,                     /* NE_OP  */
  YYSYMBOL_AND_OP = 16,                    /* AND_OP  */
  YYSYMBOL_OR_OP = 17,                     /* OR_OP  */
  YYSYMBOL_MUL_ASSIGN = 18,                /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 19,                /* DIV_ASSIGN  */
  YYSYMBOL_MOD_ASSIGN = 20,                /* MOD_ASSIGN  */
  YYSYMBOL_ADD_ASSIGN = 21,                /* ADD_ASSIGN  */
  YYSYMBOL_SUB_ASSIGN = 22,                /* SUB_ASSIGN  */
  YYSYMBOL_LEFT_ASSIGN = 23,               /* LEFT_ASSIGN  */
  YYSYMBOL_RIGHT_ASSIGN = 24,              /* RIGHT_ASSIGN  */
  YYSYMBOL_AND_ASSIGN = 25,                /* AND_ASSIGN  */
  YYSYMBOL_XOR_ASSIGN = 26,                /* XOR_ASSIGN  */
  YYSYMBOL_OR_ASSIGN = 27,                 /* OR_ASSIGN  */
  YYSYMBOL_TYPE_NAME = 28,                 /* TYPE_NAME  */
  YYSYMBOL_TYPEDEF = 29,                   /* TYPEDEF  */
  YYSYMBOL_EXTERN = 30,                    /* EXTERN  */
  YYSYMBOL_STATIC = 31,                    /* STATIC  */
  YYSYMBOL_AUTO = 32,                      /* AUTO  */
  YYSYMBOL_REGISTER = 33,                  /* REGISTER  */
  YYSYMBOL_SIZEOF = 34,                    /* SIZEOF  */
  YYSYMBOL_CHAR = 35,                      /* CHAR  */
  YYSYMBOL_SHORT = 36,                     /* SHORT  */
  YYSYMBOL_INT = 37,                       /* INT  */
  YYSYMBOL_LONG = 38,                      /* LONG  */
  YYSYMBOL_SIGNED = 39,                    /* SIGNED  */
  YYSYMBOL_UNSIGNED = 40,                  /* UNSIGNED  */
  YYSYMBOL_FLOAT = 41,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 42,                    /* DOUBLE  */
  YYSYMBOL_CONST = 43,                     /* CONST  */
  YYSYMBOL_VOLATILE = 44,                  /* VOLATILE  */
  YYSYMBOL_VOID = 45,                      /* VOID  */
  YYSYMBOL_STRUCT = 46,                    /* STRUCT  */
  YYSYMBOL_UNION = 47,                     /* UNION  */
  YYSYMBOL_ENUM = 48,                      /* ENUM  */
  YYSYMBOL_ELLIPSIS = 49,                  /* ELLIPSIS  */
  YYSYMBOL_CASE = 50,                      /* CASE  */
  YYSYMBOL_DEFAULT = 51,                   /* DEFAULT  */
  YYSYMBOL_IF = 52,                        /* IF  */
  YYSYMBOL_ELSE = 53,                      /* ELSE  */
  YYSYMBOL_SWITCH = 54,                    /* SWITCH  */
  YYSYMBOL_WHILE = 55,                     /* WHILE  */
  YYSYMBOL_DO = 56,                        /* DO  */
  YYSYMBOL_FOR = 57,                       /* FOR  */
  YYSYMBOL_GOTO = 58,                      /* GOTO  */
  YYSYMBOL_CONTINUE = 59,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 60,                     /* BREAK  */
  YYSYMBOL_RETURN = 61,                    /* RETURN  */
  YYSYMBOL_UNKNOWN = 62,                   /* UNKNOWN  */
  YYSYMBOL_63_ = 63,                       /* '('  */
  YYSYMBOL_64_ = 64,                       /* ')'  */
  YYSYMBOL_65_ = 65,                       /* '['  */
  YYSYMBOL_66_ = 66,                       /* ']'  */
  YYSYMBOL_67_ = 67,                       /* '.'  */
  YYSYMBOL_68_ = 68,                       /* ','  */
  YYSYMBOL_69_ = 69,                       /* '&'  */
  YYSYMBOL_70_ = 70,                       /* '*'  */
  YYSYMBOL_71_ = 71,                       /* '+'  */
  YYSYMBOL_72_ = 72,                       /* '-'  */
  YYSYMBOL_73_ = 73,                       /* '~'  */
  YYSYMBOL_74_ = 74,                       /* '!'  */
  YYSYMBOL_75_ = 75,                       /* '/'  */
  YYSYMBOL_76_ = 76,                       /* '%'  */
  YYSYMBOL_77_ = 77,                       /* '<'  */
  YYSYMBOL_78_ = 78,                       /* '>'  */
  YYSYMBOL_79_ = 79,                       /* '^'  */
  YYSYMBOL_80_ = 80,                       /* '|'  */
  YYSYMBOL_81_ = 81,                       /* '?'  */
  YYSYMBOL_82_ = 82,                       /* ':'  */
  YYSYMBOL_83_ = 83,                       /* '='  */
  YYSYMBOL_84_ = 84,                       /* ';'  */
  YYSYMBOL_85_ = 85,                       /* '{'  */
  YYSYMBOL_86_ = 86,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 87,                  /* $accept  */
  YYSYMBOL_ROOT = 88,                      /* ROOT  */
  YYSYMBOL_translation_unit = 89,          /* translation_unit  */
  YYSYMBOL_external_declaration = 90,      /* external_declaration  */
  YYSYMBOL_function_definition = 91,       /* function_definition  */
  YYSYMBOL_primary_expression = 92,        /* primary_expression  */
  YYSYMBOL_postfix_expression = 93,        /* postfix_expression  */
  YYSYMBOL_argument_expression_list = 94,  /* argument_expression_list  */
  YYSYMBOL_unary_expression = 95,          /* unary_expression  */
  YYSYMBOL_unary_operator = 96,            /* unary_operator  */
  YYSYMBOL_cast_expression = 97,           /* cast_expression  */
  YYSYMBOL_multiplicative_expression = 98, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 99,       /* additive_expression  */
  YYSYMBOL_shift_expression = 100,         /* shift_expression  */
  YYSYMBOL_relational_expression = 101,    /* relational_expression  */
  YYSYMBOL_equality_expression = 102,      /* equality_expression  */
  YYSYMBOL_and_expression = 103,           /* and_expression  */
  YYSYMBOL_exclusive_or_expression = 104,  /* exclusive_or_expression  */
  YYSYMBOL_inclusive_or_expression = 105,  /* inclusive_or_expression  */
  YYSYMBOL_logical_and_expression = 106,   /* logical_and_expression  */
  YYSYMBOL_logical_or_expression = 107,    /* logical_or_expression  */
  YYSYMBOL_conditional_expression = 108,   /* conditional_expression  */
  YYSYMBOL_assignment_expression = 109,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 110,      /* assignment_operator  */
  YYSYMBOL_expression = 111,               /* expression  */
  YYSYMBOL_constant_expression = 112,      /* constant_expression  */
  YYSYMBOL_declaration = 113,              /* declaration  */
  YYSYMBOL_declaration_specifiers = 114,   /* declaration_specifiers  */
  YYSYMBOL_init_declarator_list = 115,     /* init_declarator_list  */
  YYSYMBOL_init_declarator = 116,          /* init_declarator  */
  YYSYMBOL_storage_class_specifier = 117,  /* storage_class_specifier  */
  YYSYMBOL_type_specifier = 118,           /* type_specifier  */
  YYSYMBOL_struct_specifier = 119,         /* struct_specifier  */
  YYSYMBOL_struct_declaration_list = 120,  /* struct_declaration_list  */
  YYSYMBOL_struct_declaration = 121,       /* struct_declaration  */
  YYSYMBOL_specifier_qualifier_list = 122, /* specifier_qualifier_list  */
  YYSYMBOL_struct_declarator_list = 123,   /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 124,        /* struct_declarator  */
  YYSYMBOL_enum_definition = 125,          /* enum_definition  */
  YYSYMBOL_enum_specifier = 126,           /* enum_specifier  */
  YYSYMBOL_enumerator_list = 127,          /* enumerator_list  */
  YYSYMBOL_enumerator = 128,               /* enumerator  */
  YYSYMBOL_declarator = 129,               /* declarator  */
  YYSYMBOL_direct_declarator = 130,        /* direct_declarator  */
  YYSYMBOL_pointer = 131,                  /* pointer  */
  YYSYMBOL_parameter_list = 132,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 133,    /* parameter_declaration  */
  YYSYMBOL_identifier_list = 134,          /* identifier_list  */
  YYSYMBOL_type_name = 135,                /* type_name  */
  YYSYMBOL_abstract_declarator = 136,      /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 137, /* direct_abstract_declarator  */
  YYSYMBOL_initializer = 138,              /* initializer  */
  YYSYMBOL_initializer_list = 139,         /* initializer_list  */
  YYSYMBOL_statement = 140,                /* statement  */
  YYSYMBOL_labeled_statement = 141,        /* labeled_statement  */
  YYSYMBOL_compound_statement = 142,       /* compound_statement  */
  YYSYMBOL_declaration_list = 143,         /* declaration_list  */
  YYSYMBOL_statement_list = 144,           /* statement_list  */
  YYSYMBOL_expression_statement = 145,     /* expression_statement  */
  YYSYMBOL_selection_statement = 146,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 147,      /* iteration_statement  */
  YYSYMBOL_jump_statement = 148            /* jump_statement  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
# define YYCOPY_NEEDED 1
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  41
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1145

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  87
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  62
/* YYNRULES -- Number of rules.  */
#define YYNRULES  202
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  342

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   317


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    74,     2,     2,     2,    76,    69,     2,
      63,    64,    70,    71,    68,    72,    67,    75,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    82,    84,
      77,    83,    78,    81,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    65,     2,    66,    79,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    85,    80,    86,    73,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    67,    67,    70,    71,    75,    76,    77,    81,    82,
      83,    84,    89,    94,    98,   102,   103,   107,   108,   109,
     110,   111,   112,   113,   114,   118,   119,   125,   126,   127,
     128,   129,   130,   136,   137,   138,   139,   140,   141,   145,
     146,   150,   151,   152,   153,   157,   158,   159,   164,   165,
     166,   170,   171,   172,   173,   174,   178,   179,   180,   184,
     185,   189,   190,   194,   195,   199,   200,   204,   205,   210,
     211,   215,   219,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   244,   245,   249,   256,   257,   261,
     262,   263,   264,   269,   279,   280,   285,   286,   287,   288,
     289,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   308,   309,   310,   314,   315,   319,   323,
     324,   328,   329,   333,   334,   335,   339,   340,   341,   344,
     345,   346,   350,   351,   355,   356,   360,   361,   365,   366,
     367,   368,   369,   370,   371,   376,   377,   382,   383,   387,
     388,   389,   393,   394,   398,   403,   404,   405,   409,   410,
     411,   412,   413,   414,   415,   416,   417,   421,   422,   423,
     430,   431,   435,   436,   437,   438,   439,   440,   444,   445,
     446,   451,   452,   453,   454,   460,   461,   465,   466,   470,
     471,   475,   476,   477,   481,   482,   483,   484,   488,   489,
     490,   491,   492
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  static const char *const yy_sname[] =
  {
  "end of file", "error", "invalid token", "IDENTIFIER", "INT_CONSTANT",
  "FLOAT_CONSTANT", "STRING_LITERAL", "PTR_OP", "INC_OP", "DEC_OP",
  "LEFT_OP", "RIGHT_OP", "LE_OP", "GE_OP", "EQ_OP", "NE_OP", "AND_OP",
  "OR_OP", "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "ADD_ASSIGN",
  "SUB_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN", "AND_ASSIGN", "XOR_ASSIGN",
  "OR_ASSIGN", "TYPE_NAME", "TYPEDEF", "EXTERN", "STATIC", "AUTO",
  "REGISTER", "SIZEOF", "CHAR", "SHORT", "INT", "LONG", "SIGNED",
  "UNSIGNED", "FLOAT", "DOUBLE", "CONST", "VOLATILE", "VOID", "STRUCT",
  "UNION", "ENUM", "ELLIPSIS", "CASE", "DEFAULT", "IF", "ELSE", "SWITCH",
  "WHILE", "DO", "FOR", "GOTO", "CONTINUE", "BREAK", "RETURN", "UNKNOWN",
  "'('", "')'", "'['", "']'", "'.'", "','", "'&'", "'*'", "'+'", "'-'",
  "'~'", "'!'", "'/'", "'%'", "'<'", "'>'", "'^'", "'|'", "'?'", "':'",
  "'='", "';'", "'{'", "'}'", "$accept", "ROOT", "translation_unit",
  "external_declaration", "function_definition", "primary_expression",
  "postfix_expression", "argument_expression_list", "unary_expression",
  "unary_operator", "cast_expression", "multiplicative_expression",
  "additive_expression", "shift_expression", "relational_expression",
  "equality_expression", "and_expression", "exclusive_or_expression",
  "inclusive_or_expression", "logical_and_expression",
  "logical_or_expression", "conditional_expression",
  "assignment_expression", "assignment_operator", "expression",
  "constant_expression", "declaration", "declaration_specifiers",
  "init_declarator_list", "init_declarator", "storage_class_specifier",
  "type_specifier", "struct_specifier", "struct_declaration_list",
  "struct_declaration", "specifier_qualifier_list",
  "struct_declarator_list", "struct_declarator", "enum_definition",
  "enum_specifier", "enumerator_list", "enumerator", "declarator",
  "direct_declarator", "pointer", "parameter_list",
  "parameter_declaration", "identifier_list", "type_name",
  "abstract_declarator", "direct_abstract_declarator", "initializer",
  "initializer_list", "statement", "labeled_statement",
  "compound_statement", "declaration_list", "statement_list",
  "expression_statement", "selection_statement", "iteration_statement",
  "jump_statement", YY_NULLPTR
  };
  return yy_sname[yysymbol];
}
#endif

#define YYPACT_NINF (-190)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-132)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     952,  -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,
    -190,  -190,  -190,  -190,  -190,  -190,  -190,    10,    13,    59,
     -16,    41,   952,  -190,  -190,  -190,     9,  1097,  1097,  -190,
    -190,  -190,  1038,    71,    11,   -12,   557,   130,    60,    16,
    -190,  -190,  -190,  -190,     8,  -190,  1017,    28,  -190,  -190,
     268,  -190,     9,  -190,  1038,   996,   660,    71,   557,   557,
     413,  -190,    45,    60,    54,   -22,  -190,  -190,  -190,   503,
    -190,  1038,    22,    60,    61,  -190,  -190,  -190,   828,   828,
     849,   861,    88,    49,   129,   132,   556,   141,   208,   137,
     149,   575,   647,  -190,  -190,  -190,  -190,  -190,  -190,  -190,
    -190,  -190,   133,   264,   861,  -190,   105,   146,   209,    32,
     216,   159,   167,   168,   236,    39,  -190,  -190,   -47,  -190,
    -190,  -190,   340,   412,  -190,  -190,  -190,  -190,   170,  -190,
    -190,  -190,  -190,    56,    -3,  -190,    64,  -190,  -190,  -190,
    -190,   189,   485,  -190,  -190,  -190,   861,   -26,  -190,   174,
     -18,   861,    60,   173,   503,  -190,  -190,  -190,    60,   -11,
     556,   861,  -190,  -190,   647,  -190,   176,   556,   861,   861,
     861,   206,   628,   178,  -190,  -190,  -190,    -2,   108,  -190,
     200,   262,  -190,  -190,   732,   861,   263,  -190,  -190,  -190,
    -190,  -190,  -190,  -190,  -190,  -190,  -190,  -190,   861,  -190,
     861,   861,   861,   861,   861,   861,   861,   861,   861,   861,
     861,   861,   861,   861,   861,   861,   861,   861,   861,   861,
    -190,  -190,   484,  -190,  -190,   908,   744,  -190,    68,  -190,
     119,  -190,  1097,  -190,   265,  -190,  -190,  -190,    45,  -190,
     861,   183,  -190,  -190,  -190,     2,   100,  -190,  -190,   205,
     556,  -190,   109,   115,   123,   207,   628,  -190,  -190,  -190,
     861,  -190,  -190,   125,  -190,   144,  -190,  -190,  -190,  -190,
    -190,   105,   105,   146,   146,   209,   209,   209,   209,    32,
      32,   216,   159,   167,   168,   236,    29,  -190,  -190,  -190,
     126,   211,  -190,   212,   119,  1076,   756,  -190,  -190,  -190,
    -190,   431,  -190,  -190,  -190,  -190,   556,   556,   556,   861,
     777,  -190,  -190,   861,  -190,   861,  -190,  -190,  -190,  -190,
     138,  -190,   213,  -190,  -190,   227,  -190,  -190,   139,   556,
     145,  -190,  -190,  -190,  -190,   556,   197,  -190,   556,  -190,
    -190,  -190
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   138,   112,    96,    97,    98,    99,   100,   102,   103,
     104,   105,   108,   109,   106,   107,   101,     0,     0,     0,
     145,     0,     2,     3,     5,     6,     0,    89,    91,   110,
       7,   111,     0,   137,     0,   115,     0,   128,     0,     0,
     146,     1,     4,    87,     0,    93,    94,     0,    90,    92,
       0,   185,     0,    11,     0,     0,     0,   136,     0,   120,
       0,   116,     0,     0,   134,     0,   132,   139,    88,     0,
       9,     0,   131,     0,    12,    13,    14,    15,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    33,    34,    35,    36,    37,    38,   189,
     181,    17,    27,    39,     0,    41,    45,    48,    51,    56,
      59,    61,    63,    65,    67,    69,    71,    84,     0,   187,
     172,   173,     0,     0,   174,   175,   176,   177,    94,   186,
      10,   152,   144,   151,     0,   147,     0,    12,   141,    39,
      86,     0,     0,   119,   114,   117,     0,     0,   121,   123,
       0,     0,     0,   126,     0,   167,    95,     8,     0,     0,
       0,     0,    28,    29,     0,    31,     0,     0,     0,     0,
       0,     0,     0,     0,   199,   200,   201,     0,     0,   154,
       0,     0,    23,    24,     0,     0,     0,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    73,     0,    30,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     190,   183,     0,   182,   188,     0,     0,   149,   155,   150,
     156,   142,     0,   143,     0,   140,   113,   124,     0,   118,
       0,   127,   135,   133,   170,     0,     0,   129,   178,     0,
       0,   180,     0,     0,     0,     0,     0,   198,   202,    16,
       0,    22,    19,     0,    25,     0,    21,    72,    42,    43,
      44,    46,    47,    49,    50,    54,    55,    52,    53,    57,
      58,    60,    62,    64,    66,    68,     0,    85,   184,   163,
       0,     0,   159,     0,   157,     0,     0,   148,   153,   122,
     125,     0,   168,   130,    32,   179,     0,     0,     0,     0,
       0,    40,    20,     0,    18,     0,   164,   158,   160,   165,
       0,   161,     0,   169,   171,   191,   193,   194,     0,     0,
       0,    26,    70,   166,   162,     0,     0,   196,     0,   192,
     195,   197
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -190,  -190,  -190,   270,  -190,  -190,  -190,  -190,   -55,  -190,
     -97,    46,    37,    30,    24,    80,    97,    79,    96,    98,
    -190,   -52,   -54,  -190,   -83,   -62,    47,     0,  -190,  -190,
    -190,   -25,  -190,   259,   -28,   -41,  -190,    83,  -190,  -190,
     -33,   180,    -9,   -29,   -17,  -189,   101,  -190,   166,   110,
     106,  -134,  -190,   -84,  -190,     6,   151,   214,  -166,  -190,
    -190,  -190
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    21,    22,    23,    24,   101,   102,   263,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   198,   118,   141,    51,    52,    44,    45,
      27,    28,    29,    60,    61,    62,   147,   148,    30,    31,
      65,    66,    32,    33,    34,   134,   135,   136,   180,   229,
     230,   156,   245,   119,   120,   121,    54,   123,   124,   125,
     126,   127
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      26,   139,   171,    40,   140,    57,   256,   199,   177,   178,
      39,    59,     1,    35,     1,   155,    37,    46,   143,   166,
     244,   219,    26,   162,   163,   165,   139,    48,    49,   140,
     150,    72,   145,    59,    59,    59,   290,   220,    53,   224,
     159,    41,   238,   128,   207,   208,   152,    25,     1,   139,
     152,   179,    70,   149,    20,   133,   217,   152,   239,     1,
     130,   231,     1,    64,   153,   232,   219,    59,   241,    25,
     301,     1,    19,    58,    19,   247,   248,   157,   178,    20,
      67,   178,   258,   251,   237,   252,   253,   254,   302,   242,
     310,   139,    68,    43,   140,    36,   139,   219,    38,   140,
     155,   129,   265,   268,   269,   270,   320,   158,    19,   209,
     210,   315,   168,    73,   145,    20,   228,    59,   129,   225,
     218,   226,    19,   179,   227,   246,    20,   146,   233,    20,
     264,   225,   234,   226,    55,   286,    56,   151,   224,    59,
     181,   182,   183,   160,   267,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   311,   293,   287,   305,   324,   152,   129,
     167,   139,   259,   306,   140,   200,   219,   219,   300,   307,
     201,   202,   295,   219,   296,   139,   303,   308,   140,   312,
     316,   219,   169,   313,   232,   170,   184,    71,   185,    57,
     186,   122,   333,   336,   172,   139,   232,   219,   228,   338,
     314,   173,   219,   219,  -131,    63,    39,   203,   204,   205,
     206,   174,   325,   326,   327,   133,   328,   330,   213,   149,
     211,   212,   133,   175,   322,   279,   280,   275,   276,   277,
     278,   139,   273,   274,   140,   337,   214,   155,   215,   271,
     272,   339,   216,    69,   341,   235,   240,  -129,   250,   331,
     139,   255,   257,   332,   260,   261,   266,  -130,   298,   304,
     309,    74,    75,    76,    77,   317,    78,    79,   318,   334,
     335,   340,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,    42,   281,   283,   133,     2,     3,     4,     5,
       6,     7,    80,     8,     9,    10,    11,    12,    13,    14,
      15,   282,   284,    16,    17,   285,    47,   142,    81,    82,
      83,   299,    84,    85,    86,    87,    88,    89,    90,    91,
     249,    92,   243,   297,   294,   291,   222,    93,    94,    95,
      96,    97,    98,    74,    75,    76,    77,   197,    78,    79,
       0,     0,    99,    50,   100,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     2,     3,
       4,     5,     6,     7,    80,     8,     9,    10,    11,    12,
      13,    14,    15,     0,     0,    16,    17,     0,    47,     0,
      81,    82,    83,     0,    84,    85,    86,    87,    88,    89,
      90,    91,     0,    92,     0,     0,     0,     0,     0,    93,
      94,    95,    96,    97,    98,    74,    75,    76,    77,     0,
      78,    79,     0,     0,    99,    50,   221,     0,     0,     0,
       0,     0,     0,     0,   137,    75,    76,    77,     0,    78,
      79,     2,     0,     0,     0,     0,    80,     0,     8,     9,
      10,    11,    12,    13,    14,    15,     0,     0,    16,    17,
       0,    47,    81,    82,    83,    80,    84,    85,    86,    87,
      88,    89,    90,    91,     0,    92,     0,     0,     0,     0,
       0,    93,    94,    95,    96,    97,    98,    74,    75,    76,
      77,     0,    78,    79,    92,     0,    99,    50,   223,   144,
      93,    94,    95,    96,    97,    98,   137,    75,    76,    77,
       0,    78,    79,     2,     0,     0,   154,   323,    80,     0,
       8,     9,    10,    11,    12,    13,    14,    15,     0,     0,
      16,    17,     0,    47,    81,    82,    83,    80,    84,    85,
      86,    87,    88,    89,    90,    91,     0,    92,     0,     0,
       0,     0,     0,    93,    94,    95,    96,    97,    98,    74,
      75,    76,    77,     0,    78,    79,    92,     0,    99,    50,
     288,   236,    93,    94,    95,    96,    97,    98,   137,    75,
      76,    77,     0,    78,    79,     2,     0,     0,   154,     0,
      80,     0,     8,     9,    10,    11,    12,    13,    14,    15,
       0,     0,    16,    17,     0,    47,    81,    82,    83,    80,
      84,    85,    86,    87,    88,    89,    90,    91,     0,    92,
       0,     0,     0,     0,     0,    93,    94,    95,    96,    97,
      98,   137,    75,    76,    77,     0,    78,    79,    92,     0,
      99,    50,     0,     0,    93,    94,    95,    96,    97,    98,
     137,    75,    76,    77,     0,    78,    79,     0,     0,   176,
       0,     0,    80,   137,    75,    76,    77,     0,    78,    79,
       0,     0,     0,     0,     0,     2,     0,     0,     0,     0,
       0,    80,     8,     9,    10,    11,    12,    13,    14,    15,
       0,    92,    16,    17,    80,    47,     0,    93,    94,    95,
      96,    97,    98,     0,     0,     0,     0,     0,     0,     0,
      92,     0,    99,     0,     0,     0,    93,    94,    95,    96,
      97,    98,     0,    92,     0,     0,   138,     0,     0,    93,
      94,    95,    96,    97,    98,   137,    75,    76,    77,     0,
      78,    79,     0,     0,     0,     0,     0,   137,    75,    76,
      77,     0,    78,    79,     0,     0,     0,     0,     0,   137,
      75,    76,    77,     0,    78,    79,    80,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    80,     0,
     137,    75,    76,    77,     0,    78,    79,     0,     0,     0,
      80,     0,     0,     0,     0,    92,   262,     0,     0,     0,
       0,    93,    94,    95,    96,    97,    98,    92,     0,     0,
     292,    80,     0,    93,    94,    95,    96,    97,    98,    92,
       0,     0,   321,     0,     0,    93,    94,    95,    96,    97,
      98,   137,    75,    76,    77,     0,    78,    79,     0,     0,
      92,   329,     0,     0,     0,     0,    93,    94,    95,    96,
      97,    98,   137,    75,    76,    77,     0,    78,    79,     0,
       0,     0,    80,     0,   137,    75,    76,    77,     0,    78,
      79,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    80,     0,     0,     0,     0,     0,     0,
       0,   161,     0,     0,     0,    80,     0,    93,    94,    95,
      96,    97,    98,     0,     0,     0,     0,     0,     0,     0,
       0,     1,   164,     0,     0,     0,     0,     0,    93,    94,
      95,    96,    97,    98,    92,     0,     0,     0,     0,     0,
      93,    94,    95,    96,    97,    98,     2,     3,     4,     5,
       6,     7,     0,     8,     9,    10,    11,    12,    13,    14,
      15,     0,     0,    16,    17,     1,    47,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   225,   289,   226,     0,     0,     0,     0,    20,     0,
       2,     3,     4,     5,     6,     7,     0,     8,     9,    10,
      11,    12,    13,    14,    15,     0,     0,    16,    17,   131,
      18,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    19,     0,     0,     0,     0,
       0,     0,    20,     0,     2,     3,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    13,    14,    15,     0,
       0,    16,    17,     0,    47,     2,     3,     4,     5,     6,
       7,     0,     8,     9,    10,    11,    12,    13,    14,    15,
     132,     0,    16,    17,     0,    47,     2,     3,     4,     5,
       6,     7,     0,     8,     9,    10,    11,    12,    13,    14,
      15,     0,     0,    16,    17,     0,    47,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      69,     0,    50,     0,     2,     3,     4,     5,     6,     7,
       0,     8,     9,    10,    11,    12,    13,    14,    15,     0,
       0,    16,    17,    50,    47,     2,     3,     4,     5,     6,
       7,     0,     8,     9,    10,    11,    12,    13,    14,    15,
     319,     0,    16,    17,     0,    47
};

static const yytype_int16 yycheck[] =
{
       0,    56,    86,    20,    56,    34,   172,   104,    91,    92,
      19,    36,     3,     3,     3,    69,     3,    26,    59,    81,
     154,    68,    22,    78,    79,    80,    81,    27,    28,    81,
      63,     3,    60,    58,    59,    60,   225,    84,    32,   123,
      73,     0,    68,    52,    12,    13,    68,     0,     3,   104,
      68,    92,    46,    62,    70,    55,    17,    68,    84,     3,
      54,    64,     3,     3,    86,    68,    68,    92,    86,    22,
      68,     3,    63,    85,    63,    86,   160,    71,   161,    70,
      64,   164,    84,   167,   146,   168,   169,   170,    86,   151,
     256,   146,    84,    84,   146,    85,   151,    68,    85,   151,
     154,    54,   185,   200,   201,   202,   295,    85,    63,    77,
      78,    82,    63,    85,   142,    70,   133,   142,    71,    63,
      81,    65,    63,   164,   133,   158,    70,    82,    64,    70,
     184,    63,    68,    65,    63,   218,    65,    83,   222,   164,
       7,     8,     9,    82,   198,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   260,   226,   219,   250,   301,    68,   122,
      82,   226,    64,    64,   226,    70,    68,    68,   240,    64,
      75,    76,    63,    68,    65,   240,    86,    64,   240,    64,
      64,    68,    63,    68,    68,    63,    63,    46,    65,   228,
      67,    50,    64,    64,    63,   260,    68,    68,   225,    64,
      66,     3,    68,    68,    84,    85,   225,    71,    72,    10,
      11,    84,   306,   307,   308,   225,   309,   310,    69,   238,
      14,    15,   232,    84,   296,   211,   212,   207,   208,   209,
     210,   296,   205,   206,   296,   329,    79,   301,    80,   203,
     204,   335,    16,    83,   338,    66,    82,    84,    82,   313,
     315,    55,    84,   315,    64,     3,     3,    84,     3,    64,
      63,     3,     4,     5,     6,    64,     8,     9,    66,    66,
      53,    84,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    22,   213,   215,   295,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,   214,   216,    45,    46,   217,    48,    58,    50,    51,
      52,   238,    54,    55,    56,    57,    58,    59,    60,    61,
     164,    63,   152,   232,   228,   225,   122,    69,    70,    71,
      72,    73,    74,     3,     4,     5,     6,    83,     8,     9,
      -1,    -1,    84,    85,    86,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    -1,    -1,    45,    46,    -1,    48,    -1,
      50,    51,    52,    -1,    54,    55,    56,    57,    58,    59,
      60,    61,    -1,    63,    -1,    -1,    -1,    -1,    -1,    69,
      70,    71,    72,    73,    74,     3,     4,     5,     6,    -1,
       8,     9,    -1,    -1,    84,    85,    86,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,    -1,     8,
       9,    28,    -1,    -1,    -1,    -1,    34,    -1,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,    -1,    45,    46,
      -1,    48,    50,    51,    52,    34,    54,    55,    56,    57,
      58,    59,    60,    61,    -1,    63,    -1,    -1,    -1,    -1,
      -1,    69,    70,    71,    72,    73,    74,     3,     4,     5,
       6,    -1,     8,     9,    63,    -1,    84,    85,    86,    86,
      69,    70,    71,    72,    73,    74,     3,     4,     5,     6,
      -1,     8,     9,    28,    -1,    -1,    85,    86,    34,    -1,
      35,    36,    37,    38,    39,    40,    41,    42,    -1,    -1,
      45,    46,    -1,    48,    50,    51,    52,    34,    54,    55,
      56,    57,    58,    59,    60,    61,    -1,    63,    -1,    -1,
      -1,    -1,    -1,    69,    70,    71,    72,    73,    74,     3,
       4,     5,     6,    -1,     8,     9,    63,    -1,    84,    85,
      86,    86,    69,    70,    71,    72,    73,    74,     3,     4,
       5,     6,    -1,     8,     9,    28,    -1,    -1,    85,    -1,
      34,    -1,    35,    36,    37,    38,    39,    40,    41,    42,
      -1,    -1,    45,    46,    -1,    48,    50,    51,    52,    34,
      54,    55,    56,    57,    58,    59,    60,    61,    -1,    63,
      -1,    -1,    -1,    -1,    -1,    69,    70,    71,    72,    73,
      74,     3,     4,     5,     6,    -1,     8,     9,    63,    -1,
      84,    85,    -1,    -1,    69,    70,    71,    72,    73,    74,
       3,     4,     5,     6,    -1,     8,     9,    -1,    -1,    84,
      -1,    -1,    34,     3,     4,     5,     6,    -1,     8,     9,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      -1,    63,    45,    46,    34,    48,    -1,    69,    70,    71,
      72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      63,    -1,    84,    -1,    -1,    -1,    69,    70,    71,    72,
      73,    74,    -1,    63,    -1,    -1,    66,    -1,    -1,    69,
      70,    71,    72,    73,    74,     3,     4,     5,     6,    -1,
       8,     9,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,    -1,     8,     9,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,    -1,     8,     9,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,
       3,     4,     5,     6,    -1,     8,     9,    -1,    -1,    -1,
      34,    -1,    -1,    -1,    -1,    63,    64,    -1,    -1,    -1,
      -1,    69,    70,    71,    72,    73,    74,    63,    -1,    -1,
      66,    34,    -1,    69,    70,    71,    72,    73,    74,    63,
      -1,    -1,    66,    -1,    -1,    69,    70,    71,    72,    73,
      74,     3,     4,     5,     6,    -1,     8,     9,    -1,    -1,
      63,    64,    -1,    -1,    -1,    -1,    69,    70,    71,    72,
      73,    74,     3,     4,     5,     6,    -1,     8,     9,    -1,
      -1,    -1,    34,    -1,     3,     4,     5,     6,    -1,     8,
       9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    -1,    -1,    -1,    34,    -1,    69,    70,    71,
      72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,    63,    -1,    -1,    -1,    -1,    -1,    69,    70,
      71,    72,    73,    74,    63,    -1,    -1,    -1,    -1,    -1,
      69,    70,    71,    72,    73,    74,    28,    29,    30,    31,
      32,    33,    -1,    35,    36,    37,    38,    39,    40,    41,
      42,    -1,    -1,    45,    46,     3,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    65,    -1,    -1,    -1,    -1,    70,    -1,
      28,    29,    30,    31,    32,    33,    -1,    35,    36,    37,
      38,    39,    40,    41,    42,    -1,    -1,    45,    46,     3,
      48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      -1,    45,    46,    -1,    48,    28,    29,    30,    31,    32,
      33,    -1,    35,    36,    37,    38,    39,    40,    41,    42,
      64,    -1,    45,    46,    -1,    48,    28,    29,    30,    31,
      32,    33,    -1,    35,    36,    37,    38,    39,    40,    41,
      42,    -1,    -1,    45,    46,    -1,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      83,    -1,    85,    -1,    28,    29,    30,    31,    32,    33,
      -1,    35,    36,    37,    38,    39,    40,    41,    42,    -1,
      -1,    45,    46,    85,    48,    28,    29,    30,    31,    32,
      33,    -1,    35,    36,    37,    38,    39,    40,    41,    42,
      64,    -1,    45,    46,    -1,    48
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    28,    29,    30,    31,    32,    33,    35,    36,
      37,    38,    39,    40,    41,    42,    45,    46,    48,    63,
      70,    88,    89,    90,    91,   113,   114,   117,   118,   119,
     125,   126,   129,   130,   131,     3,    85,     3,    85,   129,
     131,     0,    90,    84,   115,   116,   129,    48,   114,   114,
      85,   113,   114,   142,   143,    63,    65,   130,    85,   118,
     120,   121,   122,    85,     3,   127,   128,    64,    84,    83,
     142,   143,     3,    85,     3,     4,     5,     6,     8,     9,
      34,    50,    51,    52,    54,    55,    56,    57,    58,    59,
      60,    61,    63,    69,    70,    71,    72,    73,    74,    84,
      86,    92,    93,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   111,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   129,   113,
     142,     3,    64,   114,   132,   133,   134,     3,    66,    95,
     108,   112,   120,   122,    86,   121,    82,   123,   124,   129,
     127,    83,    68,    86,    85,   109,   138,   142,    85,   127,
      82,    63,    95,    95,    63,    95,   112,    82,    63,    63,
      63,   140,    63,     3,    84,    84,    84,   111,   111,   122,
     135,     7,     8,     9,    63,    65,    67,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    83,   110,    97,
      70,    75,    76,    71,    72,    10,    11,    12,    13,    77,
      78,    14,    15,    69,    79,    80,    16,    17,    81,    68,
      84,    86,   144,    86,   140,    63,    65,   129,   131,   136,
     137,    64,    68,    64,    68,    66,    86,   112,    68,    84,
      82,    86,   112,   128,   138,   139,   127,    86,   140,   135,
      82,   140,   111,   111,   111,    55,   145,    84,    84,    64,
      64,     3,    64,    94,   109,   111,     3,   109,    97,    97,
      97,    98,    98,    99,    99,   100,   100,   100,   100,   101,
     101,   102,   103,   104,   105,   106,   111,   109,    86,    64,
     132,   136,    66,   112,   137,    63,    65,   133,     3,   124,
     112,    68,    86,    86,    64,   140,    64,    64,    64,    63,
     145,    97,    64,    68,    66,    82,    64,    64,    66,    64,
     132,    66,   112,    86,   138,   140,   140,   140,   111,    64,
     111,   109,   108,    64,    66,    53,    64,   140,    64,   140,
      84,   140
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    87,    88,    89,    89,    90,    90,    90,    91,    91,
      91,    91,    92,    92,    92,    92,    92,    93,    93,    93,
      93,    93,    93,    93,    93,    94,    94,    95,    95,    95,
      95,    95,    95,    96,    96,    96,    96,    96,    96,    97,
      97,    98,    98,    98,    98,    99,    99,    99,   100,   100,
     100,   101,   101,   101,   101,   101,   102,   102,   102,   103,
     103,   104,   104,   105,   105,   106,   106,   107,   107,   108,
     108,   109,   109,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   111,   111,   112,   113,   113,   114,
     114,   114,   114,   115,   116,   116,   117,   117,   117,   117,
     117,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   119,   119,   119,   120,   120,   121,   122,
     122,   123,   123,   124,   124,   124,   125,   125,   125,   126,
     126,   126,   127,   127,   128,   128,   129,   129,   130,   130,
     130,   130,   130,   130,   130,   131,   131,   132,   132,   133,
     133,   133,   134,   134,   135,   136,   136,   136,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   138,   138,   138,
     139,   139,   140,   140,   140,   140,   140,   140,   141,   141,
     141,   142,   142,   142,   142,   143,   143,   144,   144,   145,
     145,   146,   146,   146,   147,   147,   147,   147,   148,   148,
     148,   148,   148
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     4,     3,
       3,     2,     1,     1,     1,     1,     3,     1,     4,     3,
       4,     3,     3,     2,     2,     1,     3,     1,     2,     2,
       2,     2,     4,     1,     1,     1,     1,     1,     1,     1,
       4,     1,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       5,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     2,     3,     1,
       2,     1,     2,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     5,     4,     2,     1,     2,     3,     2,
       1,     1,     3,     1,     2,     3,     4,     5,     2,     4,
       5,     2,     1,     3,     1,     3,     2,     1,     1,     3,
       4,     3,     4,     4,     3,     1,     2,     1,     3,     2,
       2,     1,     1,     3,     1,     1,     1,     2,     3,     2,
       3,     3,     4,     2,     3,     3,     4,     1,     3,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     4,
       3,     2,     3,     3,     4,     1,     2,     1,     2,     1,
       2,     5,     7,     5,     5,     7,     6,     7,     3,     2,
       2,     2,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        YY_LAC_DISCARD ("YYBACKUP");                              \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Given a state stack such that *YYBOTTOM is its bottom, such that
   *YYTOP is either its top or is YYTOP_EMPTY to indicate an empty
   stack, and such that *YYCAPACITY is the maximum number of elements it
   can hold without a reallocation, make sure there is enough room to
   store YYADD more elements.  If not, allocate a new stack using
   YYSTACK_ALLOC, copy the existing elements, and adjust *YYBOTTOM,
   *YYTOP, and *YYCAPACITY to reflect the new capacity and memory
   location.  If *YYBOTTOM != YYBOTTOM_NO_FREE, then free the old stack
   using YYSTACK_FREE.  Return 0 if successful or if no reallocation is
   required.  Return YYENOMEM if memory is exhausted.  */
static int
yy_lac_stack_realloc (YYPTRDIFF_T *yycapacity, YYPTRDIFF_T yyadd,
#if YYDEBUG
                      char const *yydebug_prefix,
                      char const *yydebug_suffix,
#endif
                      yy_state_t **yybottom,
                      yy_state_t *yybottom_no_free,
                      yy_state_t **yytop, yy_state_t *yytop_empty)
{
  YYPTRDIFF_T yysize_old =
    *yytop == yytop_empty ? 0 : *yytop - *yybottom + 1;
  YYPTRDIFF_T yysize_new = yysize_old + yyadd;
  if (*yycapacity < yysize_new)
    {
      YYPTRDIFF_T yyalloc = 2 * yysize_new;
      yy_state_t *yybottom_new;
      /* Use YYMAXDEPTH for maximum stack size given that the stack
         should never need to grow larger than the main state stack
         needs to grow without LAC.  */
      if (YYMAXDEPTH < yysize_new)
        {
          YYDPRINTF ((stderr, "%smax size exceeded%s", yydebug_prefix,
                      yydebug_suffix));
          return YYENOMEM;
        }
      if (YYMAXDEPTH < yyalloc)
        yyalloc = YYMAXDEPTH;
      yybottom_new =
        YY_CAST (yy_state_t *,
                 YYSTACK_ALLOC (YY_CAST (YYSIZE_T,
                                         yyalloc * YYSIZEOF (*yybottom_new))));
      if (!yybottom_new)
        {
          YYDPRINTF ((stderr, "%srealloc failed%s", yydebug_prefix,
                      yydebug_suffix));
          return YYENOMEM;
        }
      if (*yytop != yytop_empty)
        {
          YYCOPY (yybottom_new, *yybottom, yysize_old);
          *yytop = yybottom_new + (yysize_old - 1);
        }
      if (*yybottom != yybottom_no_free)
        YYSTACK_FREE (*yybottom);
      *yybottom = yybottom_new;
      *yycapacity = yyalloc;
    }
  return 0;
}

/* Establish the initial context for the current lookahead if no initial
   context is currently established.

   We define a context as a snapshot of the parser stacks.  We define
   the initial context for a lookahead as the context in which the
   parser initially examines that lookahead in order to select a
   syntactic action.  Thus, if the lookahead eventually proves
   syntactically unacceptable (possibly in a later context reached via a
   series of reductions), the initial context can be used to determine
   the exact set of tokens that would be syntactically acceptable in the
   lookahead's place.  Moreover, it is the context after which any
   further semantic actions would be erroneous because they would be
   determined by a syntactically unacceptable token.

   YY_LAC_ESTABLISH should be invoked when a reduction is about to be
   performed in an inconsistent state (which, for the purposes of LAC,
   includes consistent states that don't know they're consistent because
   their default reductions have been disabled).  Iff there is a
   lookahead token, it should also be invoked before reporting a syntax
   error.  This latter case is for the sake of the debugging output.

   For parse.lac=full, the implementation of YY_LAC_ESTABLISH is as
   follows.  If no initial context is currently established for the
   current lookahead, then check if that lookahead can eventually be
   shifted if syntactic actions continue from the current context.
   Report a syntax error if it cannot.  */
#define YY_LAC_ESTABLISH                                                \
do {                                                                    \
  if (!yy_lac_established)                                              \
    {                                                                   \
      YYDPRINTF ((stderr,                                               \
                  "LAC: initial context established for %s\n",          \
                  yysymbol_name (yytoken)));                            \
      yy_lac_established = 1;                                           \
      switch (yy_lac (yyesa, &yyes, &yyes_capacity, yyssp, yytoken))    \
        {                                                               \
        case YYENOMEM:                                                  \
          YYNOMEM;                                                      \
        case 1:                                                         \
          goto yyerrlab;                                                \
        }                                                               \
    }                                                                   \
} while (0)

/* Discard any previous initial lookahead context because of Event,
   which may be a lookahead change or an invalidation of the currently
   established initial context for the current lookahead.

   The most common example of a lookahead change is a shift.  An example
   of both cases is syntax error recovery.  That is, a syntax error
   occurs when the lookahead is syntactically erroneous for the
   currently established initial context, so error recovery manipulates
   the parser stacks to try to find a new initial context in which the
   current lookahead is syntactically acceptable.  If it fails to find
   such a context, it discards the lookahead.  */
#if YYDEBUG
# define YY_LAC_DISCARD(Event)                                           \
do {                                                                     \
  if (yy_lac_established)                                                \
    {                                                                    \
      YYDPRINTF ((stderr, "LAC: initial context discarded due to "       \
                  Event "\n"));                                          \
      yy_lac_established = 0;                                            \
    }                                                                    \
} while (0)
#else
# define YY_LAC_DISCARD(Event) yy_lac_established = 0
#endif

/* Given the stack whose top is *YYSSP, return 0 iff YYTOKEN can
   eventually (after perhaps some reductions) be shifted, return 1 if
   not, or return YYENOMEM if memory is exhausted.  As preconditions and
   postconditions: *YYES_CAPACITY is the allocated size of the array to
   which *YYES points, and either *YYES = YYESA or *YYES points to an
   array allocated with YYSTACK_ALLOC.  yy_lac may overwrite the
   contents of either array, alter *YYES and *YYES_CAPACITY, and free
   any old *YYES other than YYESA.  */
static int
yy_lac (yy_state_t *yyesa, yy_state_t **yyes,
        YYPTRDIFF_T *yyes_capacity, yy_state_t *yyssp, yysymbol_kind_t yytoken)
{
  yy_state_t *yyes_prev = yyssp;
  yy_state_t *yyesp = yyes_prev;
  /* Reduce until we encounter a shift and thereby accept the token.  */
  YYDPRINTF ((stderr, "LAC: checking lookahead %s:", yysymbol_name (yytoken)));
  if (yytoken == YYSYMBOL_YYUNDEF)
    {
      YYDPRINTF ((stderr, " Always Err\n"));
      return 1;
    }
  while (1)
    {
      int yyrule = yypact[+*yyesp];
      if (yypact_value_is_default (yyrule)
          || (yyrule += yytoken) < 0 || YYLAST < yyrule
          || yycheck[yyrule] != yytoken)
        {
          /* Use the default action.  */
          yyrule = yydefact[+*yyesp];
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
        }
      else
        {
          /* Use the action from yytable.  */
          yyrule = yytable[yyrule];
          if (yytable_value_is_error (yyrule))
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
          if (0 < yyrule)
            {
              YYDPRINTF ((stderr, " S%d\n", yyrule));
              return 0;
            }
          yyrule = -yyrule;
        }
      /* By now we know we have to simulate a reduce.  */
      YYDPRINTF ((stderr, " R%d", yyrule - 1));
      {
        /* Pop the corresponding number of values from the stack.  */
        YYPTRDIFF_T yylen = yyr2[yyrule];
        /* First pop from the LAC stack as many tokens as possible.  */
        if (yyesp != yyes_prev)
          {
            YYPTRDIFF_T yysize = yyesp - *yyes + 1;
            if (yylen < yysize)
              {
                yyesp -= yylen;
                yylen = 0;
              }
            else
              {
                yyesp = yyes_prev;
                yylen -= yysize;
              }
          }
        /* Only afterwards look at the main stack.  */
        if (yylen)
          yyesp = yyes_prev -= yylen;
      }
      /* Push the resulting state of the reduction.  */
      {
        yy_state_fast_t yystate;
        {
          const int yylhs = yyr1[yyrule] - YYNTOKENS;
          const int yyi = yypgoto[yylhs] + *yyesp;
          yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyesp
                     ? yytable[yyi]
                     : yydefgoto[yylhs]);
        }
        if (yyesp == yyes_prev)
          {
            yyesp = *yyes;
            YY_IGNORE_USELESS_CAST_BEGIN
            *yyesp = YY_CAST (yy_state_t, yystate);
            YY_IGNORE_USELESS_CAST_END
          }
        else
          {
            if (yy_lac_stack_realloc (yyes_capacity, 1,
#if YYDEBUG
                                      " (", ")",
#endif
                                      yyes, yyesa, &yyesp, yyes_prev))
              {
                YYDPRINTF ((stderr, "\n"));
                return YYENOMEM;
              }
            YY_IGNORE_USELESS_CAST_BEGIN
            *++yyesp = YY_CAST (yy_state_t, yystate);
            YY_IGNORE_USELESS_CAST_END
          }
        YYDPRINTF ((stderr, " G%d", yystate));
      }
    }
}

/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yy_state_t *yyesa;
  yy_state_t **yyes;
  YYPTRDIFF_T *yyes_capacity;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;

  int yyx;
  for (yyx = 0; yyx < YYNTOKENS; ++yyx)
    {
      yysymbol_kind_t yysym = YY_CAST (yysymbol_kind_t, yyx);
      if (yysym != YYSYMBOL_YYerror && yysym != YYSYMBOL_YYUNDEF)
        switch (yy_lac (yyctx->yyesa, yyctx->yyes, yyctx->yyes_capacity, yyctx->yyssp, yysym))
          {
          case YYENOMEM:
            return YYENOMEM;
          case 1:
            continue;
          default:
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = yysym;
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif



static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
       In the first two cases, it might appear that the current syntax
       error should have been detected in the previous state when yy_lac
       was invoked.  However, at that time, there might have been a
       different syntax error that discarded a different initial context
       during error recovery, leaving behind the current lookahead.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      YYDPRINTF ((stderr, "Constructing syntax error message\n"));
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else if (yyn == 0)
        YYDPRINTF ((stderr, "No expected tokens.\n"));
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.  In order to see if a particular token T is a
   valid looakhead, invoke yy_lac (YYESA, YYES, YYES_CAPACITY, YYSSP, T).

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store or if
   yy_lac returned YYENOMEM.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yystrlen (yysymbol_name (yyarg[yyi]));
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp = yystpcpy (yyp, yysymbol_name (yyarg[yyi++]));
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    yy_state_t yyesa[20];
    yy_state_t *yyes = yyesa;
    YYPTRDIFF_T yyes_capacity = 20 < YYMAXDEPTH ? 20 : YYMAXDEPTH;

  /* Whether LAC context is established.  A Boolean.  */
  int yy_lac_established = 0;
  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    {
      YY_LAC_ESTABLISH;
      goto yydefault;
    }
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      YY_LAC_ESTABLISH;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  YY_LAC_DISCARD ("shift");
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  {
    int yychar_backup = yychar;
    switch (yyn)
      {
  case 2: /* ROOT: translation_unit  */
#line 67 "src/parser.y"
                     { g_root = (yyvsp[0].node_list); }
#line 2085 "build/parser.tab.cpp"
    break;

  case 3: /* translation_unit: external_declaration  */
#line 70 "src/parser.y"
                                                                        { (yyval.node_list) = new NodeList((yyvsp[0].node)); 		}
#line 2091 "build/parser.tab.cpp"
    break;

  case 4: /* translation_unit: translation_unit external_declaration  */
#line 71 "src/parser.y"
                                                        { (yyvsp[-1].node_list)->PushBack((yyvsp[0].node)); (yyval.node_list) = (yyvsp[-1].node_list); 	}
#line 2097 "build/parser.tab.cpp"
    break;

  case 5: /* external_declaration: function_definition  */
#line 75 "src/parser.y"
                                { (yyval.node) = (yyvsp[0].node); }
#line 2103 "build/parser.tab.cpp"
    break;

  case 6: /* external_declaration: declaration  */
#line 76 "src/parser.y"
                                        { (yyval.node) = (yyvsp[0].node); }
#line 2109 "build/parser.tab.cpp"
    break;

  case 7: /* external_declaration: enum_definition  */
#line 77 "src/parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2115 "build/parser.tab.cpp"
    break;

  case 8: /* function_definition: declaration_specifiers declarator declaration_list compound_statement  */
#line 81 "src/parser.y"
                                                                                    { (yyval.node) = new FunctionDefinition((yyvsp[-3].type_specifier), (yyvsp[-2].node), (yyvsp[-1].node_list), (yyvsp[0].node));      				}
#line 2121 "build/parser.tab.cpp"
    break;

  case 9: /* function_definition: declaration_specifiers declarator compound_statement  */
#line 82 "src/parser.y"
                                                                                                        { (yyval.node) = new FunctionDefinition((yyvsp[-2].type_specifier), (yyvsp[-1].node), nullptr, (yyvsp[0].node)); 				}
#line 2127 "build/parser.tab.cpp"
    break;

  case 10: /* function_definition: declarator declaration_list compound_statement  */
#line 83 "src/parser.y"
                                                                                                                { (yyval.node) = new FunctionDefinition(TypeSpecifier::INT, (yyvsp[-2].node), (yyvsp[-1].node_list), (yyvsp[0].node)); 		}
#line 2133 "build/parser.tab.cpp"
    break;

  case 11: /* function_definition: declarator compound_statement  */
#line 84 "src/parser.y"
                                                                                                                                { (yyval.node) = new FunctionDefinition(TypeSpecifier::INT, (yyvsp[-1].node), nullptr, (yyvsp[0].node)); }
#line 2139 "build/parser.tab.cpp"
    break;

  case 12: /* primary_expression: IDENTIFIER  */
#line 89 "src/parser.y"
                     {
        std::cout << "# DEBUG: primary_expression is an IDENTIFIER: " << *(yyvsp[0].string) << std::endl;
        (yyval.node) = new Identifier(*(yyvsp[0].string));
        delete (yyvsp[0].string);
    }
#line 2149 "build/parser.tab.cpp"
    break;

  case 13: /* primary_expression: INT_CONSTANT  */
#line 94 "src/parser.y"
                       {
        std::cout << "# DEBUG: primary_expression is an INT_CONSTANT: " << (yyvsp[0].number_int) << std::endl;
        (yyval.node) = new IntConstant((yyvsp[0].number_int));
    }
#line 2158 "build/parser.tab.cpp"
    break;

  case 14: /* primary_expression: FLOAT_CONSTANT  */
#line 98 "src/parser.y"
                     {
        std::cout << "# DEBUG: primary_expression is a FLOAT_CONSTANT: " << (yyvsp[0].number_float) << std::endl;
        (yyval.node) = new FloatConstant((yyvsp[0].number_float));
    }
#line 2167 "build/parser.tab.cpp"
    break;

  case 15: /* primary_expression: STRING_LITERAL  */
#line 102 "src/parser.y"
                                { (yyval.node) = new StringLiteral(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 2173 "build/parser.tab.cpp"
    break;

  case 16: /* primary_expression: '(' expression ')'  */
#line 103 "src/parser.y"
                             { (yyval.node) = (yyvsp[-1].node); }
#line 2179 "build/parser.tab.cpp"
    break;

  case 17: /* postfix_expression: primary_expression  */
#line 107 "src/parser.y"
                                                                                                { (yyval.node) = (yyvsp[0].node); 								}
#line 2185 "build/parser.tab.cpp"
    break;

  case 18: /* postfix_expression: postfix_expression '[' expression ']'  */
#line 108 "src/parser.y"
                                                                { (yyval.node) = new ArrayIndex((yyvsp[-3].node), (yyvsp[-1].node));          }
#line 2191 "build/parser.tab.cpp"
    break;

  case 19: /* postfix_expression: postfix_expression '(' ')'  */
#line 109 "src/parser.y"
                                                                                        { (yyval.node) = new FunctionCall((yyvsp[-2].node), nullptr); 	}
#line 2197 "build/parser.tab.cpp"
    break;

  case 20: /* postfix_expression: postfix_expression '(' argument_expression_list ')'  */
#line 110 "src/parser.y"
                                                                { (yyval.node) = new FunctionCall((yyvsp[-3].node), (yyvsp[-1].node_list)); 	  	}
#line 2203 "build/parser.tab.cpp"
    break;

  case 23: /* postfix_expression: postfix_expression INC_OP  */
#line 113 "src/parser.y"
                                                                                        { (yyval.node) = new Postfixer((yyvsp[-1].node), "++"); }
#line 2209 "build/parser.tab.cpp"
    break;

  case 24: /* postfix_expression: postfix_expression DEC_OP  */
#line 114 "src/parser.y"
                                                                                        { (yyval.node) = new Postfixer((yyvsp[-1].node), "--"); }
#line 2215 "build/parser.tab.cpp"
    break;

  case 25: /* argument_expression_list: assignment_expression  */
#line 118 "src/parser.y"
                                                                                                { (yyval.node_list) = new ParameterList((yyvsp[0].node)); }
#line 2221 "build/parser.tab.cpp"
    break;

  case 26: /* argument_expression_list: argument_expression_list ',' assignment_expression  */
#line 119 "src/parser.y"
                                                                { (yyval.node_list) = (yyvsp[-2].node_list); (yyvsp[-2].node_list)->PushBack((yyvsp[0].node));  }
#line 2227 "build/parser.tab.cpp"
    break;

  case 27: /* unary_expression: postfix_expression  */
#line 125 "src/parser.y"
                                                                                                { (yyval.node) = (yyvsp[0].node);								}
#line 2233 "build/parser.tab.cpp"
    break;

  case 28: /* unary_expression: INC_OP unary_expression  */
#line 126 "src/parser.y"
                                                                                                { (yyval.node) = new Prefixer((yyvsp[0].node), "++"); 			}
#line 2239 "build/parser.tab.cpp"
    break;

  case 29: /* unary_expression: DEC_OP unary_expression  */
#line 127 "src/parser.y"
                                                                                                { (yyval.node) = new Prefixer((yyvsp[0].node), "--"); 			}
#line 2245 "build/parser.tab.cpp"
    break;

  case 30: /* unary_expression: unary_operator cast_expression  */
#line 128 "src/parser.y"
                                                                                        { (yyval.node) = new Unary(*(yyvsp[-1].string), (yyvsp[0].node)); delete (yyvsp[-1].string);	}
#line 2251 "build/parser.tab.cpp"
    break;

  case 31: /* unary_expression: SIZEOF unary_expression  */
#line 129 "src/parser.y"
                                                                                                { (yyval.node) = new SizeOf((yyvsp[0].node)); 					}
#line 2257 "build/parser.tab.cpp"
    break;

  case 32: /* unary_expression: SIZEOF '(' type_name ')'  */
#line 130 "src/parser.y"
                                                                                                { (yyval.node) = new SizeOf((yyvsp[-1].type_specifier)); 					}
#line 2263 "build/parser.tab.cpp"
    break;

  case 33: /* unary_operator: '&'  */
#line 136 "src/parser.y"
                        { (yyval.string) = new std::string("&"); }
#line 2269 "build/parser.tab.cpp"
    break;

  case 34: /* unary_operator: '*'  */
#line 137 "src/parser.y"
                        { (yyval.string) = new std::string("*"); }
#line 2275 "build/parser.tab.cpp"
    break;

  case 35: /* unary_operator: '+'  */
#line 138 "src/parser.y"
                        { (yyval.string) = new std::string("+"); }
#line 2281 "build/parser.tab.cpp"
    break;

  case 36: /* unary_operator: '-'  */
#line 139 "src/parser.y"
                        { (yyval.string) = new std::string("-"); }
#line 2287 "build/parser.tab.cpp"
    break;

  case 37: /* unary_operator: '~'  */
#line 140 "src/parser.y"
                        { (yyval.string) = new std::string("~"); }
#line 2293 "build/parser.tab.cpp"
    break;

  case 38: /* unary_operator: '!'  */
#line 141 "src/parser.y"
                        { (yyval.string) = new std::string("!"); }
#line 2299 "build/parser.tab.cpp"
    break;

  case 39: /* cast_expression: unary_expression  */
#line 145 "src/parser.y"
                                                                        { (yyval.node) = (yyvsp[0].node); }
#line 2305 "build/parser.tab.cpp"
    break;

  case 41: /* multiplicative_expression: cast_expression  */
#line 150 "src/parser.y"
                                                                                        { (yyval.node) = (yyvsp[0].node); 				  }
#line 2311 "build/parser.tab.cpp"
    break;

  case 42: /* multiplicative_expression: multiplicative_expression '*' cast_expression  */
#line 151 "src/parser.y"
                                                        { (yyval.node) = new MulOp((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2317 "build/parser.tab.cpp"
    break;

  case 43: /* multiplicative_expression: multiplicative_expression '/' cast_expression  */
#line 152 "src/parser.y"
                                                        { (yyval.node) = new DivOp((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2323 "build/parser.tab.cpp"
    break;

  case 44: /* multiplicative_expression: multiplicative_expression '%' cast_expression  */
#line 153 "src/parser.y"
                                                        { (yyval.node) = new ModOp((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2329 "build/parser.tab.cpp"
    break;

  case 46: /* additive_expression: additive_expression '+' multiplicative_expression  */
#line 158 "src/parser.y"
                                                            { (yyval.node) = new AddOp((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2335 "build/parser.tab.cpp"
    break;

  case 47: /* additive_expression: additive_expression '-' multiplicative_expression  */
#line 159 "src/parser.y"
                                                            { (yyval.node) = new SubOp((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2341 "build/parser.tab.cpp"
    break;

  case 49: /* shift_expression: shift_expression LEFT_OP additive_expression  */
#line 165 "src/parser.y"
                                                        { (yyval.node) = new LeftShift((yyvsp[-2].node), (yyvsp[0].node)); 	}
#line 2347 "build/parser.tab.cpp"
    break;

  case 50: /* shift_expression: shift_expression RIGHT_OP additive_expression  */
#line 166 "src/parser.y"
                                                        { (yyval.node) = new RightShift((yyvsp[-2].node), (yyvsp[0].node)); 	}
#line 2353 "build/parser.tab.cpp"
    break;

  case 52: /* relational_expression: relational_expression '<' shift_expression  */
#line 171 "src/parser.y"
                                                        { (yyval.node) = new LessThan((yyvsp[-2].node), (yyvsp[0].node)); 			}
#line 2359 "build/parser.tab.cpp"
    break;

  case 53: /* relational_expression: relational_expression '>' shift_expression  */
#line 172 "src/parser.y"
                                                        { (yyval.node) = new GreaterThan((yyvsp[-2].node), (yyvsp[0].node)); 		}
#line 2365 "build/parser.tab.cpp"
    break;

  case 54: /* relational_expression: relational_expression LE_OP shift_expression  */
#line 173 "src/parser.y"
                                                        { (yyval.node) = new LessThanEqual((yyvsp[-2].node), (yyvsp[0].node)); 		}
#line 2371 "build/parser.tab.cpp"
    break;

  case 55: /* relational_expression: relational_expression GE_OP shift_expression  */
#line 174 "src/parser.y"
                                                        { (yyval.node) = new GreaterThanEqual((yyvsp[-2].node), (yyvsp[0].node)); 	}
#line 2377 "build/parser.tab.cpp"
    break;

  case 57: /* equality_expression: equality_expression EQ_OP relational_expression  */
#line 179 "src/parser.y"
                                                          { (yyval.node) = new IsEqual((yyvsp[-2].node), (yyvsp[0].node));       }
#line 2383 "build/parser.tab.cpp"
    break;

  case 58: /* equality_expression: equality_expression NE_OP relational_expression  */
#line 180 "src/parser.y"
                                                          { (yyval.node) = new IsNotEqual((yyvsp[-2].node), (yyvsp[0].node));    }
#line 2389 "build/parser.tab.cpp"
    break;

  case 60: /* and_expression: and_expression '&' equality_expression  */
#line 185 "src/parser.y"
                                                 { (yyval.node) = new BitAndOp((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2395 "build/parser.tab.cpp"
    break;

  case 62: /* exclusive_or_expression: exclusive_or_expression '^' and_expression  */
#line 190 "src/parser.y"
                                                     { (yyval.node) = new BitXorOp((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2401 "build/parser.tab.cpp"
    break;

  case 64: /* inclusive_or_expression: inclusive_or_expression '|' exclusive_or_expression  */
#line 195 "src/parser.y"
                                                              { (yyval.node) = new BitOrOp((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2407 "build/parser.tab.cpp"
    break;

  case 66: /* logical_and_expression: logical_and_expression AND_OP inclusive_or_expression  */
#line 200 "src/parser.y"
                                                                { (yyval.node) = new LogAndOp((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2413 "build/parser.tab.cpp"
    break;

  case 68: /* logical_or_expression: logical_or_expression OR_OP logical_and_expression  */
#line 205 "src/parser.y"
                                                             { (yyval.node) = new LogOrOp((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2419 "build/parser.tab.cpp"
    break;

  case 71: /* assignment_expression: conditional_expression  */
#line 215 "src/parser.y"
                             {
        std::cout << "# DEBUG: assignment_expression is a conditional_expression" << std::endl;
        (yyval.node) = (yyvsp[0].node);
    }
#line 2428 "build/parser.tab.cpp"
    break;

  case 72: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 219 "src/parser.y"
                                                                 {
        std::cout << "# DEBUG: assignment_expression contains an assignment" << std::endl;
        (yyval.node) = new Assignment((yyvsp[-2].node), *(yyvsp[-1].string), (yyvsp[0].node));
        delete (yyvsp[-1].string);
    }
#line 2438 "build/parser.tab.cpp"
    break;

  case 73: /* assignment_operator: '='  */
#line 229 "src/parser.y"
                                        { (yyval.string) = new std::string("="); 	}
#line 2444 "build/parser.tab.cpp"
    break;

  case 74: /* assignment_operator: MUL_ASSIGN  */
#line 230 "src/parser.y"
                                { (yyval.string) = new std::string("*="); 	}
#line 2450 "build/parser.tab.cpp"
    break;

  case 75: /* assignment_operator: DIV_ASSIGN  */
#line 231 "src/parser.y"
                                { (yyval.string) = new std::string("/="); 	}
#line 2456 "build/parser.tab.cpp"
    break;

  case 76: /* assignment_operator: MOD_ASSIGN  */
#line 232 "src/parser.y"
                                { (yyval.string) = new std::string("%="); 	}
#line 2462 "build/parser.tab.cpp"
    break;

  case 77: /* assignment_operator: ADD_ASSIGN  */
#line 233 "src/parser.y"
                                { (yyval.string) = new std::string("+="); 	}
#line 2468 "build/parser.tab.cpp"
    break;

  case 78: /* assignment_operator: SUB_ASSIGN  */
#line 234 "src/parser.y"
                                { (yyval.string) = new std::string("-="); 	}
#line 2474 "build/parser.tab.cpp"
    break;

  case 79: /* assignment_operator: LEFT_ASSIGN  */
#line 235 "src/parser.y"
                                { (yyval.string) = new std::string("<<="); 	}
#line 2480 "build/parser.tab.cpp"
    break;

  case 80: /* assignment_operator: RIGHT_ASSIGN  */
#line 236 "src/parser.y"
                                { (yyval.string) = new std::string(">>="); 	}
#line 2486 "build/parser.tab.cpp"
    break;

  case 81: /* assignment_operator: AND_ASSIGN  */
#line 237 "src/parser.y"
                                { (yyval.string) = new std::string("&="); 	}
#line 2492 "build/parser.tab.cpp"
    break;

  case 82: /* assignment_operator: XOR_ASSIGN  */
#line 238 "src/parser.y"
                                { (yyval.string) = new std::string("^="); 	}
#line 2498 "build/parser.tab.cpp"
    break;

  case 83: /* assignment_operator: OR_ASSIGN  */
#line 239 "src/parser.y"
                                        { (yyval.string) = new std::string("|="); 	}
#line 2504 "build/parser.tab.cpp"
    break;

  case 87: /* declaration: declaration_specifiers ';'  */
#line 256 "src/parser.y"
                                                                                { (yyval.node) = new VariableDeclare((yyvsp[-1].type_specifier), nullptr);    }
#line 2510 "build/parser.tab.cpp"
    break;

  case 88: /* declaration: declaration_specifiers init_declarator_list ';'  */
#line 257 "src/parser.y"
                                                                { (yyval.node) = new VariableDeclare((yyvsp[-2].type_specifier), (yyvsp[-1].node));         }
#line 2516 "build/parser.tab.cpp"
    break;

  case 91: /* declaration_specifiers: type_specifier  */
#line 263 "src/parser.y"
                                                                                                { (yyval.type_specifier) = (yyvsp[0].type_specifier); }
#line 2522 "build/parser.tab.cpp"
    break;

  case 93: /* init_declarator_list: init_declarator  */
#line 269 "src/parser.y"
                                                                                { (yyval.node) = (yyvsp[0].node); }
#line 2528 "build/parser.tab.cpp"
    break;

  case 94: /* init_declarator: declarator  */
#line 279 "src/parser.y"
                                                        { (yyval.node) = new InitDeclare((yyvsp[0].node), nullptr); 	}
#line 2534 "build/parser.tab.cpp"
    break;

  case 95: /* init_declarator: declarator '=' initializer  */
#line 280 "src/parser.y"
                                        { (yyval.node) = new InitDeclare((yyvsp[-2].node), (yyvsp[0].node)); 		}
#line 2540 "build/parser.tab.cpp"
    break;

  case 101: /* type_specifier: VOID  */
#line 293 "src/parser.y"
                                        { (yyval.type_specifier) = TypeSpecifier::VOID; 		}
#line 2546 "build/parser.tab.cpp"
    break;

  case 102: /* type_specifier: CHAR  */
#line 294 "src/parser.y"
                                        { (yyval.type_specifier) = TypeSpecifier::CHAR; 		}
#line 2552 "build/parser.tab.cpp"
    break;

  case 103: /* type_specifier: SHORT  */
#line 295 "src/parser.y"
                                        { (yyval.type_specifier) = TypeSpecifier::SHORT; 		}
#line 2558 "build/parser.tab.cpp"
    break;

  case 104: /* type_specifier: INT  */
#line 296 "src/parser.y"
                                        { (yyval.type_specifier) = TypeSpecifier::INT; 			}
#line 2564 "build/parser.tab.cpp"
    break;

  case 105: /* type_specifier: LONG  */
#line 297 "src/parser.y"
                                        { (yyval.type_specifier) = TypeSpecifier::LONG; 		}
#line 2570 "build/parser.tab.cpp"
    break;

  case 106: /* type_specifier: FLOAT  */
#line 298 "src/parser.y"
                                        { (yyval.type_specifier) = TypeSpecifier::FLOAT; 		}
#line 2576 "build/parser.tab.cpp"
    break;

  case 107: /* type_specifier: DOUBLE  */
#line 299 "src/parser.y"
                                        { (yyval.type_specifier) = TypeSpecifier::DOUBLE; 		}
#line 2582 "build/parser.tab.cpp"
    break;

  case 108: /* type_specifier: SIGNED  */
#line 300 "src/parser.y"
                                        { (yyval.type_specifier) = TypeSpecifier::SIGNED; 		}
#line 2588 "build/parser.tab.cpp"
    break;

  case 109: /* type_specifier: UNSIGNED  */
#line 301 "src/parser.y"
                                        { (yyval.type_specifier) = TypeSpecifier::UNSIGNED; 	}
#line 2594 "build/parser.tab.cpp"
    break;

  case 111: /* type_specifier: enum_specifier  */
#line 303 "src/parser.y"
                            { (yyval.type_specifier) = TypeSpecifier::ENUM;         }
#line 2600 "build/parser.tab.cpp"
    break;

  case 126: /* enum_definition: ENUM '{' enumerator_list '}'  */
#line 339 "src/parser.y"
                                                    { (yyval.node) = new EnumSpecifier("", (yyvsp[-1].node_list)); }
#line 2606 "build/parser.tab.cpp"
    break;

  case 127: /* enum_definition: ENUM IDENTIFIER '{' enumerator_list '}'  */
#line 340 "src/parser.y"
                                                    { (yyval.node) = new EnumSpecifier(*(yyvsp[-3].string), (yyvsp[-1].node_list)); delete (yyvsp[-3].string); }
#line 2612 "build/parser.tab.cpp"
    break;

  case 128: /* enum_definition: ENUM IDENTIFIER  */
#line 341 "src/parser.y"
                                                    { (yyval.node) = new EnumSpecifier(*(yyvsp[0].string), nullptr); delete (yyvsp[0].string); }
#line 2618 "build/parser.tab.cpp"
    break;

  case 129: /* enum_specifier: ENUM '{' enumerator_list '}'  */
#line 344 "src/parser.y"
                                                    { (yyval.type_specifier) = TypeSpecifier::ENUM; }
#line 2624 "build/parser.tab.cpp"
    break;

  case 130: /* enum_specifier: ENUM IDENTIFIER '{' enumerator_list '}'  */
#line 345 "src/parser.y"
                                                    { (yyval.type_specifier) = TypeSpecifier::ENUM; delete (yyvsp[-3].string); }
#line 2630 "build/parser.tab.cpp"
    break;

  case 131: /* enum_specifier: ENUM IDENTIFIER  */
#line 346 "src/parser.y"
                                                    { (yyval.type_specifier) = TypeSpecifier::ENUM; delete (yyvsp[0].string); }
#line 2636 "build/parser.tab.cpp"
    break;

  case 132: /* enumerator_list: enumerator  */
#line 350 "src/parser.y"
                                                    { (yyval.node_list) = new NodeList((yyvsp[0].node)); }
#line 2642 "build/parser.tab.cpp"
    break;

  case 133: /* enumerator_list: enumerator_list ',' enumerator  */
#line 351 "src/parser.y"
                                                    { (yyvsp[-2].node_list)->PushBack((yyvsp[0].node)); (yyval.node_list) = (yyvsp[-2].node_list); }
#line 2648 "build/parser.tab.cpp"
    break;

  case 134: /* enumerator: IDENTIFIER  */
#line 355 "src/parser.y"
                                                    { (yyval.node) = new Enumerate(*(yyvsp[0].string), nullptr); delete (yyvsp[0].string); }
#line 2654 "build/parser.tab.cpp"
    break;

  case 135: /* enumerator: IDENTIFIER '=' constant_expression  */
#line 356 "src/parser.y"
                                                    { (yyval.node) = new Enumerate(*(yyvsp[-2].string), (yyvsp[0].node)); delete (yyvsp[-2].string); }
#line 2660 "build/parser.tab.cpp"
    break;

  case 136: /* declarator: pointer direct_declarator  */
#line 360 "src/parser.y"
                                        { (yyval.node) = new PointerDeclare((yyvsp[-1].node), (yyvsp[0].node));}
#line 2666 "build/parser.tab.cpp"
    break;

  case 137: /* declarator: direct_declarator  */
#line 361 "src/parser.y"
                                                { (yyval.node) = (yyvsp[0].node); }
#line 2672 "build/parser.tab.cpp"
    break;

  case 138: /* direct_declarator: IDENTIFIER  */
#line 365 "src/parser.y"
                                                                                                { (yyval.node) = new Identifier(*(yyvsp[0].string)); delete (yyvsp[0].string);      }
#line 2678 "build/parser.tab.cpp"
    break;

  case 140: /* direct_declarator: direct_declarator '[' constant_expression ']'  */
#line 367 "src/parser.y"
                                                            { (yyval.node) = new ArrayDeclare((yyvsp[-3].node), (yyvsp[-1].node));              }
#line 2684 "build/parser.tab.cpp"
    break;

  case 142: /* direct_declarator: direct_declarator '(' parameter_list ')'  */
#line 369 "src/parser.y"
                                                                        { (yyval.node) = new DirectDeclarator((yyvsp[-3].node), (yyvsp[-1].node_list));        }
#line 2690 "build/parser.tab.cpp"
    break;

  case 144: /* direct_declarator: direct_declarator '(' ')'  */
#line 371 "src/parser.y"
                                                                                { (yyval.node) = new DirectDeclarator((yyvsp[-2].node), nullptr);   }
#line 2696 "build/parser.tab.cpp"
    break;

  case 145: /* pointer: '*'  */
#line 376 "src/parser.y"
                                        { (yyval.node) = new Pointers(nullptr);}
#line 2702 "build/parser.tab.cpp"
    break;

  case 147: /* parameter_list: parameter_declaration  */
#line 382 "src/parser.y"
                                                        { (yyval.node_list) = new ParameterList((yyvsp[0].node));	}
#line 2708 "build/parser.tab.cpp"
    break;

  case 148: /* parameter_list: parameter_list ',' parameter_declaration  */
#line 383 "src/parser.y"
                                                        { (yyval.node_list) = (yyvsp[-2].node_list); (yyvsp[-2].node_list)->PushBack((yyvsp[0].node));    }
#line 2714 "build/parser.tab.cpp"
    break;

  case 149: /* parameter_declaration: declaration_specifiers declarator  */
#line 387 "src/parser.y"
                                                            { (yyval.node) = new ParameterDeclare((yyvsp[-1].type_specifier), (yyvsp[0].node)); 		}
#line 2720 "build/parser.tab.cpp"
    break;

  case 150: /* parameter_declaration: declaration_specifiers abstract_declarator  */
#line 388 "src/parser.y"
                                                                { (yyval.node) = new ParameterDeclare((yyvsp[-1].type_specifier), nullptr); 	}
#line 2726 "build/parser.tab.cpp"
    break;

  case 154: /* type_name: specifier_qualifier_list  */
#line 398 "src/parser.y"
                                   {(yyval.type_specifier) = (yyvsp[0].type_specifier); }
#line 2732 "build/parser.tab.cpp"
    break;

  case 167: /* initializer: assignment_expression  */
#line 421 "src/parser.y"
                                                { (yyval.node) = (yyvsp[0].node); }
#line 2738 "build/parser.tab.cpp"
    break;

  case 168: /* initializer: '{' initializer_list '}'  */
#line 422 "src/parser.y"
                                                { (yyval.node) = (yyvsp[-1].node); }
#line 2744 "build/parser.tab.cpp"
    break;

  case 169: /* initializer: '{' initializer_list ',' '}'  */
#line 423 "src/parser.y"
                                        { (yyval.node) = (yyvsp[-2].node); }
#line 2750 "build/parser.tab.cpp"
    break;

  case 170: /* initializer_list: initializer  */
#line 430 "src/parser.y"
                                                                { (yyval.node) = new NodeList((yyvsp[0].node)); }
#line 2756 "build/parser.tab.cpp"
    break;

  case 171: /* initializer_list: initializer_list ',' initializer  */
#line 431 "src/parser.y"
                                                { static_cast<NodeList*>((yyvsp[-2].node))->PushBack(NodePtr((yyvsp[0].node))); (yyval.node) = (yyvsp[-2].node);}
#line 2762 "build/parser.tab.cpp"
    break;

  case 172: /* statement: labeled_statement  */
#line 435 "src/parser.y"
                                                { (yyval.node) = (yyvsp[0].node); }
#line 2768 "build/parser.tab.cpp"
    break;

  case 173: /* statement: compound_statement  */
#line 436 "src/parser.y"
                                        { (yyval.node) = (yyvsp[0].node); }
#line 2774 "build/parser.tab.cpp"
    break;

  case 174: /* statement: expression_statement  */
#line 437 "src/parser.y"
                                        { (yyval.node) = (yyvsp[0].node); }
#line 2780 "build/parser.tab.cpp"
    break;

  case 175: /* statement: selection_statement  */
#line 438 "src/parser.y"
                                        { (yyval.node) = (yyvsp[0].node); }
#line 2786 "build/parser.tab.cpp"
    break;

  case 176: /* statement: iteration_statement  */
#line 439 "src/parser.y"
                                        { (yyval.node) = (yyvsp[0].node); }
#line 2792 "build/parser.tab.cpp"
    break;

  case 177: /* statement: jump_statement  */
#line 440 "src/parser.y"
                                                { (yyval.node) = (yyvsp[0].node); }
#line 2798 "build/parser.tab.cpp"
    break;

  case 181: /* compound_statement: '{' '}'  */
#line 451 "src/parser.y"
                                                                                        { (yyval.node) = nullptr; 				  }
#line 2804 "build/parser.tab.cpp"
    break;

  case 182: /* compound_statement: '{' statement_list '}'  */
#line 452 "src/parser.y"
                                                                        { (yyval.node) = (yyvsp[-1].node_list);                        }
#line 2810 "build/parser.tab.cpp"
    break;

  case 183: /* compound_statement: '{' declaration_list '}'  */
#line 453 "src/parser.y"
                                                                        { (yyval.node) = (yyvsp[-1].node_list);                        }
#line 2816 "build/parser.tab.cpp"
    break;

  case 184: /* compound_statement: '{' declaration_list statement_list '}'  */
#line 454 "src/parser.y"
                                                    { (yyval.node) = new CompStatement((yyvsp[-2].node_list), (yyvsp[-1].node_list)); }
#line 2822 "build/parser.tab.cpp"
    break;

  case 185: /* declaration_list: declaration  */
#line 460 "src/parser.y"
                                                                                { (yyval.node_list) = new NodeList((yyvsp[0].node)); 	}
#line 2828 "build/parser.tab.cpp"
    break;

  case 186: /* declaration_list: declaration_list declaration  */
#line 461 "src/parser.y"
                                                                { (yyvsp[-1].node_list)->PushBack((yyvsp[0].node)); (yyval.node_list)= (yyvsp[-1].node_list); }
#line 2834 "build/parser.tab.cpp"
    break;

  case 187: /* statement_list: statement  */
#line 465 "src/parser.y"
                                                                        { (yyval.node_list) = new NodeList((yyvsp[0].node)); 	}
#line 2840 "build/parser.tab.cpp"
    break;

  case 188: /* statement_list: statement_list statement  */
#line 466 "src/parser.y"
                                                                { (yyvsp[-1].node_list)->PushBack((yyvsp[0].node)); (yyval.node_list)= (yyvsp[-1].node_list); }
#line 2846 "build/parser.tab.cpp"
    break;

  case 190: /* expression_statement: expression ';'  */
#line 471 "src/parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 2852 "build/parser.tab.cpp"
    break;

  case 191: /* selection_statement: IF '(' expression ')' statement  */
#line 475 "src/parser.y"
                                                                                { (yyval.node) = new IfStatement((yyvsp[-2].node), (yyvsp[0].node));     }
#line 2858 "build/parser.tab.cpp"
    break;

  case 192: /* selection_statement: IF '(' expression ')' statement ELSE statement  */
#line 476 "src/parser.y"
                                                                { (yyval.node) = new IfElse((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));      }
#line 2864 "build/parser.tab.cpp"
    break;

  case 194: /* iteration_statement: WHILE '(' expression ')' statement  */
#line 481 "src/parser.y"
                                                                                                                            { (yyval.node) = new WhileStatement((yyvsp[-2].node), (yyvsp[0].node));       }
#line 2870 "build/parser.tab.cpp"
    break;

  case 197: /* iteration_statement: FOR '(' expression_statement expression_statement expression ')' statement  */
#line 484 "src/parser.y"
                                                                                        { (yyval.node) = new ForStatement((yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2876 "build/parser.tab.cpp"
    break;

  case 199: /* jump_statement: CONTINUE ';'  */
#line 489 "src/parser.y"
                                 { (yyval.node) = new ContinueStatement();        }
#line 2882 "build/parser.tab.cpp"
    break;

  case 200: /* jump_statement: BREAK ';'  */
#line 490 "src/parser.y"
                                 { (yyval.node) = new BreakKeyWord();             }
#line 2888 "build/parser.tab.cpp"
    break;

  case 201: /* jump_statement: RETURN ';'  */
#line 491 "src/parser.y"
                                         { (yyval.node) = new ReturnStatement(nullptr);   }
#line 2894 "build/parser.tab.cpp"
    break;

  case 202: /* jump_statement: RETURN expression ';'  */
#line 492 "src/parser.y"
                                 { (yyval.node) = new ReturnStatement((yyvsp[-1].node));        }
#line 2900 "build/parser.tab.cpp"
    break;


#line 2904 "build/parser.tab.cpp"

        default: break;
      }
    if (yychar_backup != yychar)
      YY_LAC_DISCARD ("yychar change");
  }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yyesa, &yyes, &yyes_capacity, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        if (yychar != YYEMPTY)
          YY_LAC_ESTABLISH;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  /* If the stack popping above didn't lose the initial context for the
     current lookahead token, the shift below will for sure.  */
  YY_LAC_DISCARD ("error recovery");

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yyes != yyesa)
    YYSTACK_FREE (yyes);
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 495 "src/parser.y"


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
