#ifndef __CONDITION_H_
#define __CONDITION_H_

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
   Expression *expr1, *expr2;
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

Condition *Eq(Expression *expr1, Expression *expr2);
Condition *Lt(Expression *expr1, Expression *expr2);
Condition *Gt(Expression *expr1, Expression *expr2);
Condition *Leq(Expression *expr1, Expression *expr2);
Condition *Geq(Expression *expr1, Expression *expr2);
Condition *And(Condition *cond1, Condition *cond2);
Condition *Or(Condition *cond1, Condition *cond2);
Condition *Not(Condition *cond);

typedef Condition * (*binCondFunc) (Expression *, Expression *);

void deleteCondition(Condition *cond);
void printCondition(Condition *cond);

#endif