/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CREATE = 258,
     TABLE = 259,
     INSERT = 260,
     INTO = 261,
     SELECT = 262,
     FROM = 263,
     WHERE = 264,
     PRIMARY = 265,
     FOREIGN = 266,
     KEY = 267,
     DEFAULT = 268,
     CHECK = 269,
     NOT = 270,
     TOKEN_NULL = 271,
     AND = 272,
     OR = 273,
     NEQ = 274,
     GEQ = 275,
     LEQ = 276,
     REFERENCES = 277,
     ORDER = 278,
     BY = 279,
     DELETE = 280,
     AS = 281,
     INT = 282,
     DOUBLE = 283,
     CHAR = 284,
     VARCHAR = 285,
     TEXT = 286,
     USING = 287,
     JOIN = 288,
     INNER = 289,
     OUTER = 290,
     LEFT = 291,
     RIGHT = 292,
     NATURAL = 293,
     UNION = 294,
     VALUES = 295,
     AUTO = 296,
     INCREMENT = 297,
     ASC = 298,
     DESC = 299,
     UNIQUE = 300,
     IN = 301,
     ON = 302,
     COUNT = 303,
     SUM = 304,
     AVG = 305,
     MIN = 306,
     MAX = 307,
     IDENTIFIER = 308,
     STRING_LITERAL = 309,
     DOUBLE_LITERAL = 310,
     INT_LITERAL = 311
   };
#endif
/* Tokens.  */
#define CREATE 258
#define TABLE 259
#define INSERT 260
#define INTO 261
#define SELECT 262
#define FROM 263
#define WHERE 264
#define PRIMARY 265
#define FOREIGN 266
#define KEY 267
#define DEFAULT 268
#define CHECK 269
#define NOT 270
#define TOKEN_NULL 271
#define AND 272
#define OR 273
#define NEQ 274
#define GEQ 275
#define LEQ 276
#define REFERENCES 277
#define ORDER 278
#define BY 279
#define DELETE 280
#define AS 281
#define INT 282
#define DOUBLE 283
#define CHAR 284
#define VARCHAR 285
#define TEXT 286
#define USING 287
#define JOIN 288
#define INNER 289
#define OUTER 290
#define LEFT 291
#define RIGHT 292
#define NATURAL 293
#define UNION 294
#define VALUES 295
#define AUTO 296
#define INCREMENT 297
#define ASC 298
#define DESC 299
#define UNIQUE 300
#define IN 301
#define ON 302
#define COUNT 303
#define SUM 304
#define AVG 305
#define MIN 306
#define MAX 307
#define IDENTIFIER 308
#define STRING_LITERAL 309
#define DOUBLE_LITERAL 310
#define INT_LITERAL 311




/* Copy the first part of user declarations.  */
#line 1 "sql.y"


#include <stdio.h>
#include <stdlib.h>

void yyerror(char *s);
int yylex(void);
#define YYDEBUG 0
int yydebug=0;
int to_print = 0;
int num_stmts = 0;

void puts_mod(const char *line) {
	if (to_print) { puts(line); }
}



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 19 "sql.y"
{
	double dval;
	int ival;
	const char *strval;
}
/* Line 193 of yacc.c.  */
#line 232 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 245 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  40
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   222

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  69
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  118
/* YYNRULES -- Number of states.  */
#define YYNSTATES  206

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   311

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      58,    59,    66,    64,    60,    65,    68,    67,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    57,
      63,    61,    62,     2,     2,     2,     2,     2,     2,     2,
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
      55,    56
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    13,    15,    17,    19,
      20,    27,    29,    33,    37,    39,    41,    46,    48,    50,
      52,    54,    56,    58,    60,    66,    73,    76,    82,    84,
      85,    87,    90,    93,    95,    98,   102,   105,   108,   110,
     113,   115,   119,   125,   129,   131,   132,   134,   137,   139,
     141,   143,   146,   150,   155,   160,   162,   166,   170,   176,
     180,   183,   185,   187,   189,   191,   193,   195,   197,   199,
     201,   205,   209,   213,   215,   219,   223,   225,   229,   232,
     234,   236,   238,   242,   247,   249,   251,   253,   255,   257,
     259,   261,   263,   265,   267,   271,   275,   278,   283,   285,
     289,   292,   294,   297,   301,   305,   308,   310,   311,   320,
     324,   325,   327,   331,   333,   337,   339,   341,   343
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      70,     0,    -1,    71,    -1,    70,    71,    -1,    72,    57,
      -1,    73,    -1,    86,    -1,   111,    -1,   116,    -1,    -1,
       3,     4,   105,    58,    74,    59,    -1,    75,    -1,    75,
      60,    74,    -1,   104,    76,    82,    -1,    78,    -1,    77,
      -1,    77,    58,    56,    59,    -1,    27,    -1,    28,    -1,
      29,    -1,    30,    -1,    31,    -1,    79,    -1,    80,    -1,
      10,    12,    58,   113,    59,    -1,    11,    12,    58,   104,
      59,    81,    -1,    22,   105,    -1,    22,   105,    58,   104,
      59,    -1,    83,    -1,    -1,    84,    -1,    84,    83,    -1,
      15,    16,    -1,    45,    -1,    10,    12,    -1,    11,    12,
      81,    -1,    13,    85,    -1,    14,    93,    -1,   115,    -1,
      41,    42,    -1,    87,    -1,    86,    39,    87,    -1,     7,
      97,     8,   106,    88,    -1,    58,    87,    59,    -1,    89,
      -1,    -1,    90,    -1,    89,    90,    -1,   107,    -1,    91,
      -1,    92,    -1,     9,    93,    -1,    23,    24,   104,    -1,
      23,    24,   104,    43,    -1,    23,    24,   104,    44,    -1,
      94,    -1,    94,    95,    93,    -1,    98,    96,    98,    -1,
      98,    46,    58,    86,    59,    -1,    58,    93,    59,    -1,
      15,    94,    -1,    17,    -1,    18,    -1,    61,    -1,    62,
      -1,    63,    -1,    20,    -1,    21,    -1,    19,    -1,    98,
      -1,    97,    60,    98,    -1,    98,    64,    99,    -1,    98,
      65,    99,    -1,    99,    -1,    99,    66,   100,    -1,    99,
      67,   100,    -1,   100,    -1,    58,    98,    59,    -1,    65,
     100,    -1,   101,    -1,   115,    -1,   103,    -1,   105,    68,
     103,    -1,   102,    58,    98,    59,    -1,    48,    -1,    49,
      -1,    50,    -1,    51,    -1,    52,    -1,    66,    -1,   104,
      -1,    53,    -1,    53,    -1,   108,    -1,   106,    60,   108,
      -1,   108,   109,   108,    -1,    47,    93,    -1,    32,    58,
     113,    59,    -1,   105,    -1,   105,    26,    53,    -1,   105,
      53,    -1,    33,    -1,    34,    33,    -1,    36,   110,    33,
      -1,    37,   110,    33,    -1,    38,    33,    -1,    35,    -1,
      -1,     5,     6,   105,   112,    40,    58,   114,    59,    -1,
      58,   113,    59,    -1,    -1,   104,    -1,   104,    60,   113,
      -1,   115,    -1,   115,    60,   114,    -1,    56,    -1,    55,
      -1,    54,    -1,    25,     8,   105,    91,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    42,    42,    43,    47,    51,    52,    53,    54,    55,
      59,    63,    64,    68,    69,    73,    74,    78,    79,    80,
      81,    82,    86,    87,    91,    95,    99,   100,   104,   105,
     109,   110,   114,   115,   116,   117,   118,   119,   123,   124,
     128,   129,   133,   134,   138,   139,   143,   144,   148,   149,
     150,   154,   158,   159,   160,   164,   165,   169,   170,   171,
     172,   176,   176,   180,   180,   180,   180,   180,   180,   184,
     185,   189,   190,   191,   195,   196,   197,   201,   202,   203,
     207,   208,   209,   210,   214,   214,   214,   214,   214,   218,
     219,   223,   227,   231,   232,   233,   237,   238,   242,   243,
     244,   248,   249,   250,   251,   252,   256,   257,   261,   265,
     266,   270,   271,   275,   276,   280,   281,   282,   286
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CREATE", "TABLE", "INSERT", "INTO",
  "SELECT", "FROM", "WHERE", "PRIMARY", "FOREIGN", "KEY", "DEFAULT",
  "CHECK", "NOT", "TOKEN_NULL", "AND", "OR", "NEQ", "GEQ", "LEQ",
  "REFERENCES", "ORDER", "BY", "DELETE", "AS", "INT", "DOUBLE", "CHAR",
  "VARCHAR", "TEXT", "USING", "JOIN", "INNER", "OUTER", "LEFT", "RIGHT",
  "NATURAL", "UNION", "VALUES", "AUTO", "INCREMENT", "ASC", "DESC",
  "UNIQUE", "IN", "ON", "COUNT", "SUM", "AVG", "MIN", "MAX", "IDENTIFIER",
  "STRING_LITERAL", "DOUBLE_LITERAL", "INT_LITERAL", "';'", "'('", "')'",
  "','", "'='", "'>'", "'<'", "'+'", "'-'", "'*'", "'/'", "'.'", "$accept",
  "sql_queries", "sql_query", "sql_line", "create_table",
  "column_dec_list", "column_dec", "column_type", "type", "key_dec",
  "primary_key_dec", "foreign_key_dec", "references_stmt",
  "opt_constraints", "constraints", "constraint", "default_stmt", "select",
  "select_statement", "opt_select_constraints", "select_constraints",
  "select_constraint", "where_condition", "orderby", "bool_expression",
  "bool_term", "bool_op", "comp_op", "expression_list", "expression",
  "mulexp", "primary", "term", "function_name", "column_name_or_star",
  "column_name", "table_name", "table", "join_condition", "table_def",
  "join", "opt_outer", "insert_into", "column_names", "column_names_list",
  "values_list", "literal_value", "delete_from", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,    59,    40,    41,
      44,    61,    62,    60,    43,    45,    42,    47,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    69,    70,    70,    71,    72,    72,    72,    72,    72,
      73,    74,    74,    75,    75,    76,    76,    77,    77,    77,
      77,    77,    78,    78,    79,    80,    81,    81,    82,    82,
      83,    83,    84,    84,    84,    84,    84,    84,    85,    85,
      86,    86,    87,    87,    88,    88,    89,    89,    90,    90,
      90,    91,    92,    92,    92,    93,    93,    94,    94,    94,
      94,    95,    95,    96,    96,    96,    96,    96,    96,    97,
      97,    98,    98,    98,    99,    99,    99,   100,   100,   100,
     101,   101,   101,   101,   102,   102,   102,   102,   102,   103,
     103,   104,   105,   106,   106,   106,   107,   107,   108,   108,
     108,   109,   109,   109,   109,   109,   110,   110,   111,   112,
     112,   113,   113,   114,   114,   115,   115,   115,   116
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     1,     1,     1,     1,     0,
       6,     1,     3,     3,     1,     1,     4,     1,     1,     1,
       1,     1,     1,     1,     5,     6,     2,     5,     1,     0,
       1,     2,     2,     1,     2,     3,     2,     2,     1,     2,
       1,     3,     5,     3,     1,     0,     1,     2,     1,     1,
       1,     2,     3,     4,     4,     1,     3,     3,     5,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     1,     3,     3,     1,     3,     2,     1,
       1,     1,     3,     4,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     2,     4,     1,     3,
       2,     1,     2,     3,     3,     2,     1,     0,     8,     3,
       0,     1,     3,     1,     3,     1,     1,     1,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       9,     0,     0,     0,     0,     0,     9,     2,     0,     5,
       6,    40,     7,     8,     0,     0,    84,    85,    86,    87,
      88,    91,   117,   116,   115,     0,     0,    89,     0,    69,
      73,    76,    79,     0,    81,    90,     0,    80,     0,     0,
       1,     3,     4,     0,    92,     0,   110,     0,    78,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    43,    41,
       0,     0,     0,    77,    98,    45,    93,    70,    71,    72,
      74,    75,     0,    91,    82,     0,   118,     0,     0,     0,
      11,    14,    22,    23,     0,   111,     0,     0,     0,   100,
       0,     0,     0,     0,    42,    44,    46,    49,    50,    48,
     101,     0,   107,   107,     0,     0,    83,     0,     0,    51,
      55,     0,     0,     0,    10,     0,    17,    18,    19,    20,
      21,    29,    15,     0,   109,     0,    99,     0,     0,    96,
      94,    47,   102,   106,     0,     0,   105,    95,    60,     0,
       0,    61,    62,     0,    68,    66,    67,     0,    63,    64,
      65,     0,     0,     0,    12,     0,     0,     0,     0,     0,
      33,    13,    28,    30,     0,   112,     0,   113,    52,     0,
     103,   104,    59,    56,     0,    57,     0,     0,    34,     0,
       0,    36,    38,    37,    32,    31,     0,   108,     0,    53,
      54,    97,     0,    24,     0,     0,    35,    39,    16,   114,
      58,    25,    26,     0,     0,    27
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    79,    80,   121,   122,    81,
      82,    83,   196,   161,   162,   163,   181,    10,    11,    94,
      95,    96,    97,    98,   109,   110,   143,   151,    28,   111,
      30,    31,    32,    33,    34,    35,    36,    65,    99,    66,
     105,   134,    12,    62,    86,   166,    37,    13
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -120
static const yytype_int16 yypact[] =
{
       6,    18,    24,   110,    29,     8,     7,  -120,    23,  -120,
       9,  -120,  -120,  -120,    42,    42,  -120,  -120,  -120,  -120,
    -120,    -5,  -120,  -120,  -120,   110,   110,  -120,    13,    71,
      77,  -120,  -120,    40,  -120,  -120,    38,  -120,    42,    50,
    -120,  -120,  -120,     8,  -120,    57,    63,   -36,  -120,    42,
     110,   110,   110,   110,   110,   110,    -6,   104,  -120,  -120,
      41,    75,    84,  -120,     1,    10,    96,    71,    77,    77,
    -120,  -120,    -3,  -120,  -120,    34,  -120,   138,   155,   113,
     109,  -120,  -120,  -120,   111,   114,   118,   115,   117,  -120,
     147,   120,    34,    42,  -120,    11,  -120,  -120,  -120,  -120,
    -120,   146,   145,   145,   149,    42,  -120,    34,    34,  -120,
      60,    91,   125,   126,  -120,    41,  -120,  -120,  -120,  -120,
    -120,   112,   127,    75,  -120,    49,  -120,    75,    75,  -120,
    -120,  -120,  -120,  -120,   153,   154,  -120,  -120,  -120,   129,
      55,  -120,  -120,    34,  -120,  -120,  -120,   131,  -120,  -120,
    -120,   110,    75,    75,  -120,   178,   179,   -15,    34,   176,
    -120,  -120,  -120,   112,   137,  -120,   135,   136,   102,   139,
    -120,  -120,  -120,  -120,     8,    71,   140,   141,  -120,   173,
     159,  -120,  -120,  -120,  -120,  -120,   143,  -120,    49,  -120,
    -120,  -120,   -23,  -120,   173,    42,  -120,  -120,  -120,  -120,
    -120,  -120,   148,    75,   144,  -120
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -120,  -120,   191,  -120,  -120,    89,  -120,  -120,  -120,  -120,
    -120,  -120,    14,  -120,    44,  -120,  -120,    31,     3,  -120,
    -120,   116,   152,  -120,   -90,   103,  -120,  -120,  -120,     0,
      97,    -9,  -120,  -120,   156,   -56,   -14,  -120,  -120,   -12,
    -120,   119,  -120,  -120,   -21,    25,  -119,  -120
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -93
static const yytype_int16 yytable[] =
{
      45,    46,   129,    29,    84,    85,   167,    40,    39,     1,
       1,     2,     2,     3,     3,     3,    43,    48,   139,    75,
      75,    49,    14,    63,    57,    47,   180,    88,    51,    52,
      15,     4,     4,    90,    90,    64,   200,    38,   182,    22,
      23,    24,    91,    91,    70,    71,    59,    73,    43,   107,
      67,    77,    78,   173,    89,    72,   106,    92,    92,    84,
      27,    51,    52,   -92,     5,     5,     5,    85,   183,   167,
      93,   168,    85,    50,   144,   145,   146,   141,   142,    64,
      42,   130,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    64,   108,   137,    73,    44,    85,   177,    55,    26,
      27,   147,   165,    22,    23,    24,    56,   169,   140,    58,
     144,   145,   146,    75,    63,    60,   148,   149,   150,    51,
      52,    61,   155,   156,    87,   157,   158,   159,    73,   100,
     101,   176,   102,   103,   104,    51,    52,   147,   116,   117,
     118,   119,   120,    53,    54,   189,   190,   204,    68,    69,
     112,   175,   148,   149,   150,    51,    52,   160,    16,    17,
      18,    19,    20,    21,    22,    23,    24,   113,    25,   115,
     126,   127,   114,   125,   123,    26,    27,   124,   128,   132,
     133,   202,   136,   152,   153,   164,   170,   171,   172,   174,
     178,   179,   184,   186,   187,   195,   188,    41,   191,   193,
     194,   197,   198,   205,   154,   192,   203,   185,   201,    76,
     138,   131,    74,   199,     0,     0,     0,     0,     0,     0,
       0,     0,   135
};

static const yytype_int16 yycheck[] =
{
      14,    15,    92,     3,    60,    61,   125,     0,     5,     3,
       3,     5,     5,     7,     7,     7,    39,    26,   108,     9,
       9,     8,     4,    59,    38,    25,    41,    26,    64,    65,
       6,    25,    25,    23,    23,    49,    59,     8,   157,    54,
      55,    56,    32,    32,    53,    54,    43,    53,    39,    15,
      50,    10,    11,   143,    53,    55,    59,    47,    47,   115,
      66,    64,    65,    68,    58,    58,    58,   123,   158,   188,
      60,   127,   128,    60,    19,    20,    21,    17,    18,    93,
      57,    93,    48,    49,    50,    51,    52,    53,    54,    55,
      56,   105,    58,   105,    53,    53,   152,   153,    58,    65,
      66,    46,   123,    54,    55,    56,    68,   128,   108,    59,
      19,    20,    21,     9,    59,    58,    61,    62,    63,    64,
      65,    58,    10,    11,    40,    13,    14,    15,    53,    33,
      34,   152,    36,    37,    38,    64,    65,    46,    27,    28,
      29,    30,    31,    66,    67,    43,    44,   203,    51,    52,
      12,   151,    61,    62,    63,    64,    65,    45,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    12,    58,    60,
      53,    24,    59,    58,    60,    65,    66,    59,    58,    33,
      35,   195,    33,    58,    58,    58,    33,    33,    59,    58,
      12,    12,    16,    56,    59,    22,    60,     6,    59,    59,
      59,    42,    59,    59,   115,   174,    58,   163,   194,    57,
     107,    95,    56,   188,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   103
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     7,    25,    58,    70,    71,    72,    73,
      86,    87,   111,   116,     4,     6,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    58,    65,    66,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   115,     8,    87,
       0,    71,    57,    39,    53,   105,   105,    98,   100,     8,
      60,    64,    65,    66,    67,    58,    68,   105,    59,    87,
      58,    58,   112,    59,   105,   106,   108,    98,    99,    99,
     100,   100,    98,    53,   103,     9,    91,    10,    11,    74,
      75,    78,    79,    80,   104,   104,   113,    40,    26,    53,
      23,    32,    47,    60,    88,    89,    90,    91,    92,   107,
      33,    34,    36,    37,    38,   109,    59,    15,    58,    93,
      94,    98,    12,    12,    59,    60,    27,    28,    29,    30,
      31,    76,    77,    60,    59,    58,    53,    24,    58,    93,
     108,    90,    33,    35,   110,   110,    33,   108,    94,    93,
      98,    17,    18,    95,    19,    20,    21,    46,    61,    62,
      63,    96,    58,    58,    74,    10,    11,    13,    14,    15,
      45,    82,    83,    84,    58,   113,   114,   115,   104,   113,
      33,    33,    59,    93,    58,    98,   113,   104,    12,    12,
      41,    85,   115,    93,    16,    83,    56,    59,    60,    43,
      44,    59,    86,    59,    59,    22,    81,    42,    59,   114,
      59,    81,   105,    58,   104,    59
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:
#line 47 "sql.y"
    { printf("parsed %d valid SQL statements\n", ++num_stmts); }
    break;

  case 5:
#line 51 "sql.y"
    { puts_mod ("you created a table."); }
    break;

  case 6:
#line 52 "sql.y"
    { puts_mod ("you selected something."); }
    break;

  case 7:
#line 53 "sql.y"
    { puts_mod ("you inserted a row."); }
    break;

  case 8:
#line 54 "sql.y"
    { puts_mod ("you deleted a row."); }
    break;

  case 10:
#line 59 "sql.y"
    { puts_mod ("you created a table."); }
    break;

  case 11:
#line 63 "sql.y"
    { puts_mod ("you entered a column dec list"); }
    break;

  case 13:
#line 68 "sql.y"
    { puts_mod ("you entered a column dec"); }
    break;

  case 15:
#line 73 "sql.y"
    { puts_mod ("you entered a column type."); }
    break;

  case 16:
#line 74 "sql.y"
    { puts_mod ("you entered a column type with a size."); }
    break;

  case 51:
#line 154 "sql.y"
    { puts_mod("parsed a where clause"); }
    break;

  case 71:
#line 189 "sql.y"
    { puts_mod ("you entered exp + mulexp"); }
    break;

  case 72:
#line 190 "sql.y"
    { puts_mod ("you entered exp - mulexp"); }
    break;

  case 73:
#line 191 "sql.y"
    { puts_mod ("you entered mulexp"); }
    break;

  case 74:
#line 195 "sql.y"
    { puts_mod ("you entered mulexp * primary"); }
    break;

  case 75:
#line 196 "sql.y"
    { puts_mod ("you entered mulexp / primary"); }
    break;

  case 76:
#line 197 "sql.y"
    { puts_mod ("you entered primary"); }
    break;

  case 77:
#line 201 "sql.y"
    { puts_mod ("you entered (expression)"); }
    break;

  case 78:
#line 202 "sql.y"
    { puts_mod ("you entered -primary"); }
    break;

  case 79:
#line 203 "sql.y"
    { puts_mod ("you entered a primary term"); }
    break;

  case 82:
#line 209 "sql.y"
    { puts_mod ("you entered a table name and column."); }
    break;

  case 83:
#line 210 "sql.y"
    { puts_mod ("you entered a function."); }
    break;

  case 89:
#line 218 "sql.y"
    { puts_mod("you entered *\n"); }
    break;

  case 90:
#line 219 "sql.y"
    { puts_mod ("you entered a column."); }
    break;

  case 91:
#line 223 "sql.y"
    { if (to_print) printf("found a column name '%s'\n", (yyvsp[(1) - (1)].strval)); }
    break;

  case 92:
#line 227 "sql.y"
    { puts_mod("found a table name"); }
    break;

  case 108:
#line 261 "sql.y"
    { puts_mod("you inserted something.");}
    break;


/* Line 1267 of yacc.c.  */
#line 1779 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 289 "sql.y"

