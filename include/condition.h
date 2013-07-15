#include "common.h"
#include "expression.h"

/*
data Condition = Eq Expression Expression
                | Lt Expression Expression
                | Gt Expression Expression
                | And Condition Condition
                | Or Condition Condition
                | Not Condition
*/

typedef struct CondComp {
   char *col1, *col2;
} CondComp;

typedef struct CondBinary {
   Condition *cond1, *cond2;
} CondBinary;

typedef struct CondUnary {
   Condition *cond;
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
   } cond;
};

Condition *Eq(const char *col1, const char *col2);
Condition *Lt(const char *col1, const char *col2);
Condition *Gt(const char *col1, const char *col2);
Condition *Leq(const char *col1, const char *col2);
Condition *Geq(const char *col1, const char *col2);
Condition *And(Condition *cond1, Condition *cond2);
Condition *Or(Condition *cond1, Condition *cond2);
Condition *Not(Condition *cond);

void deleteCondition(Condition *cond);
void printCondition(Condition *cond);