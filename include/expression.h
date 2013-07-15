#ifndef __EXPRESSION_H_
#define __EXPRESSION_H_

#include "common.h"
#include "literal.h"
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
   TERM_ID
};

typedef struct ExprTerm {
   enum TermType t;
   union {
      char *id;
      LiteralVal *val;
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
};


Expression *Term(const char *str);
Expression *TermLiteral(LiteralVal *val);
Expression *Plus(Expression *, Expression *);
Expression *Minus(Expression *, Expression *);
Expression *Multiply(Expression *, Expression *);
Expression *Divide(Expression *, Expression *);
Expression *Concat(Expression *, Expression *);
Expression *Neg(Expression *);

#endif