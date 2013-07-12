#ifndef __RA_H_
#define __RA_H_

#include "common.h"

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

typedef struct RATable {
   char *name;
} RATable;

typedef struct RASelect {
   Condition *expr;
   RA *ra;
} RASelect;

typedef struct RAProject {
   unsigned num_cols;
   char **cols;
   RA *ra;
} RAProject;

typedef struct RABinary {
   RA *ra1, *ra2;
} RABinary;

typedef struct RARename {
   char *table_name;
   unsigned num_col_names;
   char **col_names;
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
      RABinary binary;
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

typedef struct CondComp {
   char *col1, *col2;
} CondComp;

typedef struct CondAnd {
   Condition *expr1, *expr2;
} CondBinary;

typedef struct CondNot {
   Condition *expr;
} CondUnary;

enum CondType {
   RA_COND_EQ,
   RA_COND_LT,
   RA_COND_GT,
   RA_COND_LEQ,
   RA_COND_GEQ,
   RA_COND_AND,
   RA_COND_OR,
   RA_COND_NOT,
};

struct Condition {
   enum CondType t;
   union {
      CondComp comp;
      CondBinary binary;
      CondUnary unary;
   } expr;
};

void printExp(Condition *expr);
void printRA(RA *ra);

RA *Table (const char *name);
RA *Select (RA *ra, Condition *expr);
RA *Project (RA *ra, unsigned num_cols, ...);
RA *Union (RA *ra1, RA *ra2);
RA *Difference (RA *ra1, RA *ra2);
RA *Cross (RA *ra1, RA *ra2);
RA *Rename (RA *ra, const char *table_name, unsigned num_col_names, ...);

void deleteRA(RA *ra);

Condition *Eq(const char *col1, const char *col2);
Condition *Lt(const char *col1, const char *col2);
Condition *Gt(const char *col1, const char *col2);
Condition *Leq(const char *col1, const char *col2);
Condition *Geq(const char *col1, const char *col2);
Condition *And(Condition *expr1, Condition *expr2);
Condition *Or(Condition *expr1, Condition *expr2);
Condition *Not(Condition *expr);

void deleteCondition(Condition *expr);

#endif