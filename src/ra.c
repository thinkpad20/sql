#include "../include/ra.h"

void RA_print(RA *ra) {
   int i;
   switch(ra->t) {
      case RA_TABLE:
         indent_print("Table(%s)", ra->ra.table.name);
         break;
      case RA_SIGMA:
         indent_print("Sigma(");
         Condition_print(ra->ra.sigma.cond);
         printf(", ");
         upInd();
         RA_print(ra->ra.sigma.ra);
         downInd();
         indent_print(")");
         break;
      case RA_PI:
         indent_print("Pi(");
         Expression_printList(ra->ra.pi.expr_list);
         printf(", ");
         upInd();
         RA_print(ra->ra.pi.ra);
         downInd();
         indent_print(")");
         break;
      case RA_UNION:
         indent_print("Union(");
         upInd();
         RA_print(ra->ra.binary.ra1);
         indent_print(", ");
         RA_print(ra->ra.binary.ra2);
         downInd();
         indent_print(")");
         break;
      case RA_DIFFERENCE:
         indent_print("Difference(");
         upInd();
         RA_print(ra->ra.binary.ra1);
         indent_print(", ");
         RA_print(ra->ra.binary.ra2);
         downInd();
         indent_print(")");
         break;
      case RA_CROSS:
         indent_print("Cross(");
         upInd();
         RA_print(ra->ra.binary.ra1);
         indent_print(", \n");
         RA_print(ra->ra.binary.ra2);
         downInd();
         indent_print(")");
         break;
      case RA_RHO:
         indent_print("Rho(");
         printf("%s, ", ra->ra.rho.table_name);
         printf("[");
         for (i=0; i<ra->ra.rho.num_col_names; ++i) {
            if (i != 0) indent_print(", ");
            printf("%s", ra->ra.rho.col_names[i]);
         }
         printf("], ");
         upInd();
         RA_print(ra->ra.rho.ra);
         downInd();
         indent_print(")");
         break;
      default:
         puts("Unknown RA type");
   }
}

RA *Table (const char *name) {
   RA *new_ra = (RA *)calloc(1, sizeof(RA));
   new_ra->t = RA_TABLE;
   new_ra->ra.table.name = strdup(name);
   return new_ra;
}

RA *Sigma (RA *ra, Condition_t *cond) {
   RA *new_ra = (RA *)calloc(1, sizeof(RA));
   new_ra->t = RA_SIGMA;
   new_ra->ra.sigma.cond = cond;
   new_ra->ra.sigma.ra = ra;
   return new_ra;
}

RA *Pi (RA *ra, Expression_t *expr_list) {
   RA *new_ra = (RA *)calloc(1, sizeof(RA));
   new_ra->t = RA_PI;
   new_ra->ra.pi.ra = ra;
   new_ra->ra.pi.expr_list = expr_list;
   return new_ra;
}

RA *Union (RA *ra1, RA *ra2) {
   RA *new_ra = (RA *)calloc(1, sizeof(RA));
   new_ra->t = RA_UNION;
   new_ra->ra.binary.ra1 = ra1;
   new_ra->ra.binary.ra2 = ra2;
   return new_ra;
}

RA *Difference (RA *ra1, RA *ra2) {
   RA *new_ra = (RA *)calloc(1, sizeof(RA));
   new_ra->t = RA_DIFFERENCE;
   new_ra->ra.binary.ra1 = ra1;
   new_ra->ra.binary.ra2 = ra2;
   return new_ra;
}

RA *Cross (RA *ra1, RA *ra2) {
   RA *new_ra = (RA *)calloc(1, sizeof(RA));
   new_ra->t = RA_CROSS;
   new_ra->ra.binary.ra1 = ra1;
   new_ra->ra.binary.ra2 = ra2;
   return new_ra;
}

RA *Rho (RA *ra, const char *table_name, unsigned num_col_names, ...) {
   size_t i, j=0;
   va_list argp;
   va_start(argp, num_col_names);
   RA *new_ra = (RA *)calloc(1, sizeof(RA));
   new_ra->t = RA_RHO;
   new_ra->ra.rho.table_name = strdup(table_name);
   new_ra->ra.rho.num_col_names = num_col_names;
   if (num_col_names > 0) {
      new_ra->ra.rho.col_names = (char **)calloc(num_col_names, sizeof(char *));
      for (i=0; i<num_col_names; ++i)
         new_ra->ra.rho.col_names[j++] = strdup(va_arg(argp, const char *));
   }
   new_ra->ra.rho.ra = ra;
   return new_ra;
}

void deleteRA(RA *ra) {
   int i;
   switch(ra->t) {
      case RA_SIGMA:
         Condition_delete(ra->ra.sigma.cond);
         deleteRA(ra->ra.sigma.ra);
         break;
      case RA_PI:
         deleteRA(ra->ra.pi.ra);
         Expression_deleteList(ra->ra.pi.expr_list);
         break;
      case RA_UNION:
      case RA_DIFFERENCE:
      case RA_CROSS:
         deleteRA(ra->ra.binary.ra1);
         deleteRA(ra->ra.binary.ra2);
         break;
      case RA_RHO:
         deleteRA(ra->ra.rho.ra);
         for (i=0; i<ra->ra.rho.num_col_names; ++i)
            free(ra->ra.rho.col_names[i]);
         break;
      case RA_TABLE:
         free(ra->ra.table.name);
         break;
   }
   free(ra);
}

#ifdef RA_TEST

int main(int argc, char const *argv[])
{
   RA *ra1 = Pi(Sigma(Table("bazzle"), And(Eq("foo", "bar"), Lt("popo", "toto"))), 
               3, "foo", "bar", "baz"),
      *ra2 = Pi(Rho(Sigma(Cross(Rho(Table("Foo"), "f", 1, "Col1"),
                        Rho(Table("Foo"), "g", 1, "Col2")),Not(Eq("Col1","Col2"))
                  ),"res", 2, "Col1", "Col2"),2, "Col1", "Col2");
   RA_print(ra1);
   RA_print(ra2);
   deleteRA(ra1);
   deleteRA(ra2);
   return 0;
}

#endif
