#include "../include/expression.h"

Expression *Term(const char *str) {
   Expression *new_expr = (Expression *)calloc(1, sizeof(Expression));
   new_expr->t = EXPR_TERM;
   new_expr->expr.term.t = TERM_ID;
   new_expr->expr.term.id = strdup(str);
   return new_expr;
}

Expression *TermLiteral(LiteralVal *val) {
   Expression *new_expr = (Expression *)calloc(1, sizeof(Expression));
   new_expr->t = EXPR_TERM;
   new_expr->expr.term.t = TERM_LITERAL;
   new_expr->expr.term.val = val;
   return new_expr;
}

static void printTerm(ExprTerm term) {
   switch (term.t) {
      case TERM_ID:
         printf("%s", term.id);
         break;
      case TERM_LITERAL:
         printLiteralVal(term.val);
         break;
      default:
         printf("Unknown term type");
   }
}

Expression *Binary(Expression *expr1, Expression *expr2, enum ExprType t) {
   Expression *expr = (Expression *)calloc(1, sizeof(Expression));
   expr->t = t;
   expr->expr.binary.expr1 = expr1;
   expr->expr.binary.expr2 = expr2;
   return expr;
}

Expression *Plus(Expression *expr1, Expression *expr2) {
   return Binary(expr1, expr2, EXPR_PLUS);
}

Expression *Minus(Expression *expr1, Expression *expr2) {
   return Binary(expr1, expr2, EXPR_MINUS);
}

Expression *Multiply(Expression *expr1, Expression *expr2) {
   return Binary(expr1, expr2, EXPR_MULTIPLY);
}

Expression *Divide(Expression *expr1, Expression *expr2) {
   return Binary(expr1, expr2, EXPR_DIVIDE);
}

Expression *Concat(Expression *expr1, Expression *expr2) {
   return Binary(expr1, expr2, EXPR_CONCAT);
}

Expression *Neg(Expression *expr) {
   Expression *new_expr = (Expression *)calloc(1, sizeof(Expression));
   new_expr->t = EXPR_NEG;
   new_expr->expr.unary.expr = expr;
   return new_expr;
}

void printExpression(Expression *expr) {
   if (expr->t != EXPR_TERM) printf("(");
   switch (expr->t) {
      case EXPR_CONCAT:
         printExpression(expr->expr.binary.expr1);
         printf(" || ");
         printExpression(expr->expr.binary.expr2);
         break;
      case EXPR_PLUS:
         printExpression(expr->expr.binary.expr1);
         printf(" + ");
         printExpression(expr->expr.binary.expr2);
         break;
      case EXPR_MINUS:
         printExpression(expr->expr.binary.expr1);
         printf(" - ");
         printExpression(expr->expr.binary.expr2);
         break;
      case EXPR_MULTIPLY:
         printExpression(expr->expr.binary.expr1);
         printf(" * ");
         printExpression(expr->expr.binary.expr2);
         break;
      case EXPR_DIVIDE:
         printExpression(expr->expr.binary.expr1);
         printf(" / ");
         printExpression(expr->expr.binary.expr2);
         break;
      case EXPR_NEG:
         printf("-");
         printExpression(expr->expr.unary.expr);
         break;
      case EXPR_TERM:
         printTerm(expr->expr.term);
         break;
      default:
         printf("(Unknown expression type)");
   }
   if (expr->t != EXPR_TERM) printf(")");
}

/*#define EXPRESSION_TEST*/
#ifdef EXPRESSION_TEST
int main(int argc, char const *argv[])
{
   Expression *a = Term("a"),
              *b = Term("b"),
              *c = TermLiteral(litInt(5)),
              *plus = Plus(a,b),
              *mult = Multiply(plus, c);
   printExpression(mult);
   return 0;
}
#endif