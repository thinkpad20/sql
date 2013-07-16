#include "../include/expression.h"

static void deleteExpression(Expression *expr);

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

Expression *TermNull(void) {
   Expression *new_expr = (Expression *)calloc(1, sizeof(Expression));
   new_expr->t = EXPR_TERM;
   new_expr->expr.term.t = TERM_NULL;
   return new_expr;
}

Expression *TermColumnReference(ColumnReference *ref) {
   Expression *new_expr = (Expression *)calloc(1, sizeof(Expression));
   new_expr->t = EXPR_TERM;
   new_expr->expr.term.t = TERM_COLREF;
   new_expr->expr.term.ref = ref;
   return new_expr;
}

Expression *TermFunction(int functype, Expression *expr) {
   Expression *new_expr = (Expression *)calloc(1, sizeof(Expression));
   new_expr->t = EXPR_TERM;
   new_expr->expr.term.t = TERM_FUNC;
   new_expr->expr.term.f.t = functype;
   new_expr->expr.term.f.expr = expr;
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
      case TERM_NULL:
         printf("NULL");
         break;
      case TERM_COLREF:
         if (term.ref->tableName)
            printf("%s.", term.ref->tableName);
         printf("%s", term.ref->columnName);
         break;
      case TERM_FUNC:
         switch (term.f.t) {
            case FUNC_AVG:
               printf("AVG(");
               printExpression(term.f.expr);
               printf(")");
               break;
            case FUNC_COUNT:
               printf("COUNT(");
               printExpression(term.f.expr);
               printf(")");
               break;
            case FUNC_MAX:
               printf("MAX(");
               printExpression(term.f.expr);
               printf(")");
               break;
            case FUNC_MIN:
               printf("MIN(");
               printExpression(term.f.expr);
               printf(")");
               break;
            case FUNC_SUM:
               printf("SUM(");
               printExpression(term.f.expr);
               printf(")");
               break;
            default:
               printf("Unknown function");
         }
      default:
         printf("Unknown term type");
   }
}

static void deleteTerm(ExprTerm term) {
   switch (term.t) {
      case TERM_ID:
         free(term.id);
         break;
      case TERM_LITERAL:
         deleteLiteralVal(term.val);
         break;
      case TERM_NULL:
         break;
      case TERM_COLREF:
         if (term.ref->tableName)
            free(term.ref->tableName);
         free(term.ref->columnName);
         break;
      case TERM_FUNC:
         switch (term.f.t) {
            case FUNC_AVG:
               deleteExpression(term.f.expr);
               break;
            case FUNC_COUNT:
               deleteExpression(term.f.expr);
               break;
            case FUNC_MAX:
               deleteExpression(term.f.expr);
               break;
            case FUNC_MIN:
               deleteExpression(term.f.expr);
               break;
            case FUNC_SUM:
               deleteExpression(term.f.expr);
               break;
            default:
               printf("Can't delete unknown function\n");
         }
      default:
         printf("Can't delete, unknown term type");
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
         printf("(Unknown expression type '%d')", expr->t);
   }
   if (expr->t != EXPR_TERM) printf(")");
   if (expr->alias) printf(" as %s", expr->alias);
}

static Expression *app_exp(Expression *e1, Expression *e2) {
   e1->next = e2;
   return e1;
}

Expression *append_expression(Expression *e1, Expression *e2) {
   if (!e1) return e2;
   return app_exp(e1, append_expression(e1->next, e2));
}

void printExpressionList (Expression *expr) {
   int first = 1;
   printf("[");
   while (expr) {
      if (first) first = 0; else printf(", ");
      printExpression(expr);
      expr = expr->next;
   }
   printf("]");
}

Expression *add_alias(Expression *expr, const char *alias) {
   if (alias) expr->alias = strdup(alias);
   return expr;
}

static void deleteExpression(Expression *expr) {
   switch (expr->t) {
      case EXPR_CONCAT:
         deleteExpression(expr->expr.binary.expr1);
         deleteExpression(expr->expr.binary.expr2);
         break;
      case EXPR_PLUS:
         deleteExpression(expr->expr.binary.expr1);
         deleteExpression(expr->expr.binary.expr2);
         break;
      case EXPR_MINUS:
         deleteExpression(expr->expr.binary.expr1);
         deleteExpression(expr->expr.binary.expr2);
         break;
      case EXPR_MULTIPLY:
         deleteExpression(expr->expr.binary.expr1);
         deleteExpression(expr->expr.binary.expr2);
         break;
      case EXPR_DIVIDE:
         deleteExpression(expr->expr.binary.expr1);
         deleteExpression(expr->expr.binary.expr2);
         break;
      case EXPR_NEG:
         deleteExpression(expr->expr.unary.expr);
         break;
      case EXPR_TERM:
         deleteTerm(expr->expr.term);
         break;
      default:
         printf("Can't delete unknown expression type '%d')", expr->t);
   }
   if (expr->alias) free(expr->alias);
   free(expr);
}

void deleteExpressionList(Expression *expr) {

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
   append_expression(mult, plus);
   puts("");
   printExpressionList(mult);
   puts("");
   return 0;
}
#endif