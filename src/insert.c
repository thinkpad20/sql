#include "../include/insert.h"
#include "../include/ra.h"

ChiInsert *InsertInto(RA *ra, StrList *opt_col_names, LiteralVal *values) {
   ChiInsert *new_insert = (ChiInsert *)calloc(1, sizeof(ChiInsert));
   new_insert->ra = ra;
   new_insert->col_names = opt_col_names;
   new_insert->values = values;
   if (!values)
      fprintf(stderr, "Warning: no values given to insert\n");
   
   /* if there are any column names specified, ensure equal cardinality */
   if (opt_col_names) {
      while(true) {
         if (opt_col_names && !values) {
            fprintf(stderr, "Error: more column names specified than values\n");
            return NULL;
         }
         else if (!opt_col_names && values) {
            fprintf(stderr, "Error: more values specified than column names\n");
            return NULL;
         } else if (!opt_col_names && !values) {
            /* then both are the same cardinality, OK */
            break;
         }
         opt_col_names = opt_col_names->next;
         values = values->next;
      }
   }
   return new_insert;
}

void printInsert(ChiInsert *insert) {
   LiteralVal *val = insert->values;
   int first = 1;
   printf("Insert ");
   printf("[");
   while (val) {
      if (first) {
         first = 0;
      } else {
         printf(", ");
      }
      printLiteralVal(val);
      val = val->next;
   }
   printf("] into ");
   printRA(insert->ra);
   if (insert->col_names) {
      StrList *list = insert->col_names;
      first = 1;
      printf(" using columns [");
      while (list) {
         if (first) {
            first = 0;
         } else {
            printf(", ");
         }
         printf("%s", list->str);
         list = list->next;
      }
      printf("]");
   }
   puts("");
}