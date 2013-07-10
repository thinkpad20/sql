#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/*
RA in Haskell
data RA = Table String
        | Select Expression RA -- see below for Expression def
        | Project [String] RA
        | Union RA RA
        | Difference RA RA
        | Cross RA RA
        | Rename String [String] RA
*/

/* Forward declarations */
typedef struct RA RA;
typedef struct RAExpression RAExpression;

typedef struct RATable {
   const char *name;
} RATable;

typedef struct RASelect {
   RAExpression *expr;
   RA *ra;
} RASelect;

typedef struct RAProject {
   unsigned num_cols;
   const char **cols;
   RA *ra;
} RAProject;

typedef struct RAUnion {
   RA *ra1, *ra2;
} RAUnion;

typedef struct RADifference {
   RA *ra1, *ra2;
} RADifference;

typedef struct RACross {
   RA *ra1, *ra2;
} RACross;

typedef struct RARename {
   const char *table_name;
   unsigned num_col_names;
   const char **col_names;
   RA *ra;
} RARename;

enum RAType {
   RA_TABLE, 
   RA_SELECT, 
   RA_PROJECT, 
   RA_UNION, 
   RA_DIFFERENCE, 
   RA_CROSS, 
   RA_RENAME
};

struct RA {
   enum RAType t;
   union {
      RATable table;
      RASelect select;
      RAProject project;
      RAUnion _union; /* avoid union keyword */
      RADifference difference;
      RACross cross;
      RARename _rename;
   } ra;
};

/*
data Expression = Eq String String
                | Lt String String
                | Gt String String
                | And Expression Expression
                | Or Expression Expression
                | Not Expression
*/

typedef struct RAExprEq {
   const char *col1, *col2;
} RAExprEq;

typedef struct RAExprLt {
   const char *col1, *col2;
} RAExprLt;

typedef struct RAExprGt {
   const char *col1, *col2;
} RAExprGt;

typedef struct RAExprAnd {
   RAExpression *expr1, *expr2;
} RAExprAnd;

typedef struct RAExprOr {
   RAExpression *expr1, *expr2;
} RAExprOr;

typedef struct RAExprNot {
   RAExpression *expr;
} RAExprNot;

enum RAExprType {
   RA_EXPR_EQ,
   RA_EXPR_LT,
   RA_EXPR_GT,
   RA_EXPR_AND,
   RA_EXPR_OR,
   RA_EXPR_NOT,
};

struct RAExpression {
   enum RAExprType t;
   union {
      RAExprEq eq;
      RAExprLt lt;
      RAExprGt gt;
      RAExprAnd _and;
      RAExprOr _or;
      RAExprNot _not;
   } expr;
};

void printExp(RAExpression *expr);
void printRA(RA *ra);

RA *makeTable (const char *name);
RA *makeSelect (RAExpression *expr, RA *ra);
RA *makeProject (unsigned num_cols, const char **cols, RA *ra);
RA *makeUnion (RA *ra1, RA *ra2);
RA *makeDifference (RA *ra1, RA *ra2);
RA *makeCross (RA *ra1, RA *ra2);
RA *makeRename (const char *table_name, 
                unsigned num_col_names, 
                const char **col_names, 
                RA *ra);

RAExpression *makeEq(const char *col1, const char *col2);
RAExpression *makeLt(const char *col1, const char *col2);
RAExpression *makeGt(const char *col1, const char *col2);
RAExpression *makeAnd(RAExpression *expr1, RAExpression *expr2);
RAExpression *makeOr(RAExpression *expr1, RAExpression *expr2);
RAExpression *makeNot(RAExpression *expr);