#include "../include/condition.h"

void printCondition(Condition *cond) {
   if (!cond) return; /* just in case */
   switch(cond->t) {
      case RA_COND_EQ:
         printf("%s = %s", cond->cond.comp.col1, cond->cond.comp.col2);
         break;
      case RA_COND_LT:
         printf("%s < %s", cond->cond.comp.col1, cond->cond.comp.col2);
         break;
      case RA_COND_GT:
         printf("%s > %s", cond->cond.comp.col1, cond->cond.comp.col2);
         break;
      case RA_COND_LEQ:
         printf("%s <= %s", cond->cond.comp.col1, cond->cond.comp.col2);
         break;
      case RA_COND_GEQ:
         printf("%s >= %s", cond->cond.comp.col1, cond->cond.comp.col2);
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
         printf("not (");
         printCondition(cond->cond.unary.cond);
         printf(")");
         break;
      default:
         puts("Unknown condession type");
   }
}

Condition *Eq(const char *col1, const char *col2) {
   Condition *new_cond = (Condition *)calloc(1, sizeof(Condition));
   new_cond->t = RA_COND_EQ;
   new_cond->cond.comp.col1 = strdup(col1);
   new_cond->cond.comp.col2 = strdup(col2);
   return new_cond;
}

Condition *Lt(const char *col1, const char *col2) {
   Condition *new_cond = (Condition *)calloc(1, sizeof(Condition));
   new_cond->t = RA_COND_LT;
   new_cond->cond.comp.col1 = strdup(col1);
   new_cond->cond.comp.col2 = strdup(col2);
   return new_cond;
}

Condition *Gt(const char *col1, const char *col2) {
   Condition *new_cond = (Condition *)calloc(1, sizeof(Condition));
   new_cond->t = RA_COND_GT;
   new_cond->cond.comp.col1 = strdup(col1);
   new_cond->cond.comp.col2 = strdup(col2);
   return new_cond;
}

Condition *Leq(const char *col1, const char *col2) {
   Condition *new_cond = (Condition *)calloc(1, sizeof(Condition));
   new_cond->t = RA_COND_LEQ;
   new_cond->cond.comp.col1 = strdup(col1);
   new_cond->cond.comp.col2 = strdup(col2);
   return new_cond;
}

Condition *Geq(const char *col1, const char *col2) {
   Condition *new_cond = (Condition *)calloc(1, sizeof(Condition));
   new_cond->t = RA_COND_GEQ;
   new_cond->cond.comp.col1 = strdup(col1);
   new_cond->cond.comp.col2 = strdup(col2);
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
         free(cond->cond.comp.col1);
         free(cond->cond.comp.col2);
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