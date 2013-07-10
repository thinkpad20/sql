#include "ra.h"

static void custom_print(const char *format,...);
static void upInd();
static void downInd();

void printExp(RAExpression *expr) {
   switch(expr->t) {
      case RA_EXPR_EQ:
         printf("%s = %s", expr->expr.eq.col1, expr->expr.eq.col2);
         break;
      case RA_EXPR_LT:
         printf("%s < %s", expr->expr.lt.col1, expr->expr.lt.col2);
         break;
      case RA_EXPR_GT:
         printf("%s > %s", expr->expr.gt.col1, expr->expr.gt.col2);
         break;
      case RA_EXPR_AND:
         printExp(expr->expr._and.expr1);
         printf(" and ");
         printExp(expr->expr._and.expr2);
         break;
      case RA_EXPR_OR:
         printExp(expr->expr._or.expr1);
         printf(" or ");
         printExp(expr->expr._or.expr2);
         break;
      case RA_EXPR_NOT:
         printf("not ");
         printExp(expr->expr._not.expr);
         break;
      default:
         puts("Unknown expression type");
   }
}

void printRA(RA *ra) {
   int i;
   switch(ra->t) {
      case RA_TABLE:
         custom_print("%s", ra->ra.table.name);
         break;
      case RA_SELECT:
         custom_print("Select(");
         printExp(ra->ra.select.expr);
         custom_print(", ");
         upInd();
         printRA(ra->ra.select.ra);
         downInd();
         custom_print(")");
         break;
      case RA_PROJECT:
         custom_print("Project([");
         for (i=0; i<ra->ra.project.num_cols; ++i) {
            if (i != 0) custom_print(", ");
            custom_print("%s", ra->ra.project.cols[i]);
         }
         custom_print("], ");
         upInd();
         printRA(ra->ra.project.ra);
         downInd();
         custom_print(")");
         break;
      case RA_UNION:
         custom_print("Union(");
         upInd();
         printRA(ra->ra._union.ra1);
         custom_print(", ");
         printRA(ra->ra._union.ra2);
         downInd();
         custom_print(")");
         break;
      case RA_DIFFERENCE:
         custom_print("Difference(");
         upInd();
         printRA(ra->ra.difference.ra1);
         custom_print(", ");
         printRA(ra->ra.difference.ra2);
         downInd();
         custom_print(")");
         break;
      case RA_CROSS:
         custom_print("Cross(");
         upInd();
         printRA(ra->ra.cross.ra1);
         custom_print(", \n");
         printRA(ra->ra.cross.ra2);
         downInd();
         custom_print(")");
         break;
      case RA_RENAME:
         custom_print("Rename(");
         custom_print("%s, ", ra->ra._rename.table_name);
         custom_print("[");
         for (i=0; i<ra->ra.project.num_cols; ++i) {
            if (i != 0) custom_print(", ");
            custom_print("%s", ra->ra.project.cols[i]);
         }
         custom_print("], ");
         upInd();
         printRA(ra->ra._rename.ra);
         downInd();
         custom_print(")");
         break;
      default:
         puts("Unknown RA type");
   }
}

RA *_Table (const char *name) {
   RA *new_ra = (RA *)malloc(sizeof(RA));
   new_ra->t = RA_TABLE;
   new_ra->ra.table.name = name;
   return new_ra;
}

RA *_Select (RAExpression *expr, RA *ra) {
   RA *new_ra = (RA *)malloc(sizeof(RA));
   new_ra->t = RA_SELECT;
   new_ra->ra.select.expr = expr;
   new_ra->ra.select.ra = ra;
   return new_ra;
}

RA *_Project (unsigned num_cols, const char **cols, RA *ra) {
   RA *new_ra = (RA *)malloc(sizeof(RA));
   new_ra->t = RA_PROJECT;
   new_ra->ra.project.num_cols = num_cols;
   new_ra->ra.project.cols = cols;
   if (num_cols > 0)
      memcpy(new_ra->ra.project.cols, 
             cols, 
             num_cols * sizeof(const char*));
   new_ra->ra.project.ra = ra;
   return new_ra;
}

RA *_Union (RA *ra1, RA *ra2) {
   RA *new_ra = (RA *)malloc(sizeof(RA));
   new_ra->t = RA_UNION;
   new_ra->ra._union.ra1 = ra1;
   new_ra->ra._union.ra2 = ra2;
   return new_ra;
}

RA *_Difference (RA *ra1, RA *ra2) {
   RA *new_ra = (RA *)malloc(sizeof(RA));
   new_ra->t = RA_DIFFERENCE;
   new_ra->ra.difference.ra1 = ra1;
   new_ra->ra.difference.ra2 = ra2;
   return new_ra;
}

RA *_Cross (RA *ra1, RA *ra2) {
   RA *new_ra = (RA *)malloc(sizeof(RA));
   new_ra->t = RA_CROSS;
   new_ra->ra.cross.ra1 = ra1;
   new_ra->ra.cross.ra2 = ra2;
   return new_ra;
}

RA *_Rename (const char *table_name, 
                unsigned num_col_names, 
                const char **col_names, 
                RA *ra) {
   RA *new_ra = (RA *)malloc(sizeof(RA));
   new_ra->t = RA_RENAME;
   new_ra->ra._rename.table_name = table_name;
   new_ra->ra._rename.num_col_names = num_col_names;
   if (num_col_names > 0)
      memcpy(new_ra->ra._rename.col_names, 
             col_names, 
             num_col_names * sizeof(const char*));
   return new_ra;
}

RAExpression *_Eq(const char *col1, const char *col2) {
   RAExpression *new_expr = (RAExpression *)malloc(sizeof(RAExpression));
   new_expr->t = RA_EXPR_EQ;
   new_expr->expr.eq.col1 = col1;
   new_expr->expr.eq.col2 = col2;
   return new_expr;
}

RAExpression *_Lt(const char *col1, const char *col2) {
   RAExpression *new_expr = (RAExpression *)malloc(sizeof(RAExpression));
   new_expr->t = RA_EXPR_LT;
   new_expr->expr.eq.col1 = col1;
   new_expr->expr.eq.col2 = col2;
   return new_expr;
}

RAExpression *_Gt(const char *col1, const char *col2) {
   RAExpression *new_expr = (RAExpression *)malloc(sizeof(RAExpression));
   new_expr->t = RA_EXPR_GT;
   new_expr->expr.eq.col1 = col1;
   new_expr->expr.eq.col2 = col2;
   return new_expr;
}

RAExpression *_And(RAExpression *expr1, RAExpression *expr2) {
   RAExpression *new_expr = (RAExpression *)malloc(sizeof(RAExpression));
   new_expr->t = RA_EXPR_AND;
   new_expr->expr._and.expr1 = expr1;
   new_expr->expr._and.expr2 = expr2;
   return new_expr;
}

RAExpression *_Or(RAExpression *expr1, RAExpression *expr2) {
   RAExpression *new_expr = (RAExpression *)malloc(sizeof(RAExpression));
   new_expr->t = RA_EXPR_OR;
   new_expr->expr._or.expr1 = expr1;
   new_expr->expr._or.expr2 = expr2;
   return new_expr;
}

RAExpression *_Not(RAExpression *expr) {
   RAExpression *new_expr = (RAExpression *)malloc(sizeof(RAExpression));
   new_expr->t = RA_EXPR_NOT;
   new_expr->expr._not.expr = expr;
   return new_expr;
}

const char **strArr(size_t num, ...) {
   const char **res = (const char **)malloc(num * sizeof(const char *));
   size_t i, j=0;
   va_list argp;
   va_start(argp, num);
   for (i=0; i<num; ++i) {
      res[j++] = strdup(va_arg(argp, const char *));
   }
   return res;
}

#define BUF_SIZE 5000
static int ind = 0;

static void upInd() {
   ind++;
   printf("\n");
}

static void downInd() {
   ind--;
   printf("\n");
   if (ind < 0) printf("error, ind is < 0");
}

static void custom_print(const char *format,...)
{
   /* indent */
   int i;
   va_list argptr;
   char buffer[BUF_SIZE];
   if (ind < 1) ind = 0;
   for (i=0; i<ind; ++i) {
      if (i == 0)
         sprintf(buffer, "\t");
      else
         strcat(buffer, "\t");
   }
   va_start(argptr, format);
   vsnprintf(buffer + ind, BUF_SIZE, format, argptr);
   va_end(argptr);
   fputs(buffer, stdout);
   fflush(stdout);
}

int main(int argc, char const *argv[])
{
   RA *ra = _Project(3, strArr(3, "foo", "bar", "baz"), _Select(_And(_Eq("foo", "bar"), _Lt("popo", "toto")), _Table("bazzle")));
   printRA(ra);
   return 0;
}