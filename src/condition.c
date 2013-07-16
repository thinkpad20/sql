#include "../include/condition.h"

void printCondition(Condition *cond) {
   if (!cond) return; /* just in case */
   switch(cond->t) {
      case RA_COND_EQ:
         printExpression(cond->cond.comp.expr1);
         printf(" = ");
         printExpression(cond->cond.comp.expr2);
         break;
      case RA_COND_LT:
         printExpression(cond->cond.comp.expr1);
         printf(" < ");
         printExpression(cond->cond.comp.expr2);
         break;
      case RA_COND_GT:
         printExpression(cond->cond.comp.expr1);
         printf(" > ");
         printExpression(cond->cond.comp.expr2);
         break;
      case RA_COND_LEQ:
         printExpression(cond->cond.comp.expr1);
         printf(" <= ");
         printExpression(cond->cond.comp.expr2);
         break;
      case RA_COND_GEQ:
         printExpression(cond->cond.comp.expr1);
         printf(" >= ");
         printExpression(cond->cond.comp.expr2);
         break;
      case RA_COND_AND:
         printCondition(cond->cond.binary.cond1);
         printf(" and ");
         printCondition(cond->cond.binary.cond2);
         break;
      case RA_COND_OR:
         printCondition(cond->cond.binary.cond1);
         printf(" or ");
         printCondition(cond->cond.binary.cond2);
         break;
      case RA_COND_NOT:
         if (cond->cond.unary.cond->t == RA_COND_EQ) {
            printExpression(cond->cond.unary.cond->cond.comp.expr1);
            printf(" <> ");
            printExpression(cond->cond.unary.cond->cond.comp.expr2);
         } else {
            printf("not (");
            printCondition(cond->cond.unary.cond);
            printf(")");
         }
         break;
      default:
         puts("Unknown condession type");
   }
}

Condition *Eq(Expression *expr1, Expression *expr2) {
   Condition *new_cond = (Condition *)calloc(1, sizeof(Condition));
   new_cond->t = RA_COND_EQ;
   new_cond->cond.comp.expr1 = expr1;
   new_cond->cond.comp.expr2 = expr2;
   return new_cond;
}

Condition *Lt(Expression *expr1, Expression *expr2) {
   Condition *new_cond = (Condition *)calloc(1, sizeof(Condition));
   new_cond->t = RA_COND_LT;
   new_cond->cond.comp.expr1 = expr1;
   new_cond->cond.comp.expr2 = expr2;
   return new_cond;
}

Condition *Gt(Expression *expr1, Expression *expr2) {
   Condition *new_cond = (Condition *)calloc(1, sizeof(Condition));
   new_cond->t = RA_COND_GT;
   new_cond->cond.comp.expr1 = expr1;
   new_cond->cond.comp.expr2 = expr2;
   return new_cond;
}

Condition *Leq(Expression *expr1, Expression *expr2) {
   Condition *new_cond = (Condition *)calloc(1, sizeof(Condition));
   new_cond->t = RA_COND_LEQ;
   new_cond->cond.comp.expr1 = expr1;
   new_cond->cond.comp.expr2 = expr2;
   return new_cond;
}

Condition *Geq(Expression *expr1, Expression *expr2) {
   Condition *new_cond = (Condition *)calloc(1, sizeof(Condition));
   new_cond->t = RA_COND_GEQ;
   new_cond->cond.comp.expr1 = (expr1);
   new_cond->cond.comp.expr2 = (expr2);
   return new_cond;
}

Condition *And(Condition *cond1, Condition *cond2) {
   Condition *new_cond = (Condition *)calloc(1, sizeof(Condition));
   new_cond->t = RA_COND_AND;
   new_cond->cond.binary.cond1 = cond1;
   new_cond->cond.binary.cond2 = cond2;
   return new_cond;
}

Condition *Or(Condition *cond1, Condition *cond2) {
   Condition *new_cond = (Condition *)calloc(1, sizeof(Condition));
   new_cond->t = RA_COND_OR;
   new_cond->cond.binary.cond1 = cond1;
   new_cond->cond.binary.cond2 = cond2;
   return new_cond;
}

Condition *Not(Condition *cond) {
   Condition *new_cond = (Condition *)calloc(1, sizeof(Condition));
   new_cond->t = RA_COND_NOT;
   new_cond->cond.unary.cond = cond;
   return new_cond;
}

void deleteCondition(Condition *cond) {
   switch (cond->t) {
      case RA_COND_EQ:
      case RA_COND_LEQ:
      case RA_COND_GEQ:
      case RA_COND_GT:
      case RA_COND_LT:
         free(cond->cond.comp.expr1);
         free(cond->cond.comp.expr2);
         break;
      case RA_COND_AND:
      case RA_COND_OR:
         deleteCondition(cond->cond.binary.cond1);
         deleteCondition(cond->cond.binary.cond2);
         break;
      case RA_COND_NOT:
         deleteCondition(cond->cond.unary.cond);
         break;
   }
   free(cond);
}