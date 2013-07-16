#ifndef __EXPRESSION_H_
#define __EXPRESSION_H_

#include "common.h"
#include "literal.h"
#include "column.h"
/*

data Expression = Term String
                | Plus Expression Expression
                | Minus Expression Expression
                | Multiply Expression Expression
                | Divide Expression Expression
                | Concat Expression Expression
                | Neg Expression

*/

typedef struct Expression Expression;

enum TermType {
   TERM_LITERAL,
   TERM_ID,
   TERM_NULL,
   TERM_COLREF,
   TERM_FUNC,
};

enum FuncType { 
  FUNC_MAX, 
  FUNC_MIN, 
  FUNC_COUNT, 
  FUNC_AVG, 
  FUNC_SUM 
};

typedef struct Func {
  enum FuncType t;
  Expression *expr;
} Func;

typedef struct ExprTerm {
   enum TermType t;
   union {
      char *id;
      LiteralVal *val;
      ColumnReference *ref;
      Func f;
   };
} ExprTerm;

typedef struct ExprBinary {
   Expression *expr1, *expr2;
} ExprBinary;

typedef struct ExprUnary {
   Expression *expr;
} ExprUnary;

enum ExprType {
   EXPR_TERM,
   EXPR_PLUS,
   EXPR_MINUS,
   EXPR_MULTIPLY,
   EXPR_DIVIDE,
   EXPR_CONCAT,
   EXPR_NEG,
};

struct Expression {
   enum ExprType t;
   union {
      ExprTerm term;
      ExprBinary binary;
      ExprUnary unary;
   } expr;
   char *alias;
   Expression *next;
};


Expression *Term(const char *str);
Expression *TermLiteral(LiteralVal *val);
Expression *TermNull(void);
Expression *TermColumnReference(ColumnReference *ref);
Expression *TermFunction(int type, Expression *expr);


Expression *Plus(Expression *, Expression *);
Expression *Minus(Expression *, Expression *);
Expression *Multiply(Expression *, Expression *);
Expression *Divide(Expression *, Expression *);
Expression *Concat(Expression *, Expression *);
Expression *Neg(Expression *);

Expression *append_expression(Expression *expr_list, Expression *expr);
Expression *add_alias(Expression *expr, const char *alias);
void printExpression(Expression *);
void printExpressionList(Expression *);

void deleteExpressionList(Expression *);

#endif