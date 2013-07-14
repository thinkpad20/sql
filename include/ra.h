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

typedef struct RASigma {
   Condition *expr;
   RA *ra;
} RASigma;

typedef struct RAPi {
   unsigned num_cols;
   char **cols;
   RA *ra;
} RAPi;

typedef struct RABinary {
   RA *ra1, *ra2;
} RABinary;

typedef struct RARho {
   char *table_name;
   unsigned num_col_names;
   char **col_names;
   RA *ra;
} RARho;

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
      RASigma sigma;
      RAPi pi;
      RABinary binary;
      RARho rho;
   } ra;
};

/*
data Condition = Eq String String
                | Lt String String
                | Gt String String
                | And Condition Condition
                | Or Condition Condition
                | Not Condition
*/

typedef struct CondComp {
   char *col1, *col2;
} CondComp;

typedef struct CondBinary {
   Condition *expr1, *expr2;
} CondBinary;

typedef struct CondUnary {
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

void printCondition(Condition *expr);
void printRA(RA *ra);

RA *Table(const char *name);
RA *Sigma(RA *ra, Condition *expr);
RA *Pi(RA *ra, unsigned num_cols, ...);
RA *Union(RA *ra1, RA *ra2);
RA *Difference(RA *ra1, RA *ra2);
RA *Cross(RA *ra1, RA *ra2);
RA *Rho(RA *ra, const char *table_name, unsigned num_col_names, ...);

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