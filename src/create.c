#include "../include/create.h"
#include "../include/ra.h"

vector_t *tables = NULL;
static ChiTable *add_primary_key(ChiTable *table, const char *col_name);

ChiColumn *Column(const char *name, enum data_type type, Constraint *constraints) {
   ChiColumn *new_column = (ChiColumn *)calloc(1, sizeof(ChiColumn));
   new_column->name = strdup(name);
   new_column->type = type;
   new_column->constraints = constraints;
   return new_column;
}

static ChiColumn *add_constraints(ChiColumn *column, Constraint *constraints) {
   column->constraints = append_constraint(column->constraints, constraints);
   return column;
}

Constraint *append_constraint(Constraint *constraints, Constraint *constraint) {
   if (constraints == NULL)
      constraints = constraint;
   else
      constraints->next = constraint;
   return constraints;
}

void printConstraint(void *constraint_voidp) {
   Constraint *constraint = (Constraint *)constraint_voidp;
   switch(constraint->t) {
      case CONS_DEFAULT:
         printf("Default: ");
         printLiteralVal(constraint->constraint.default_val);
         break;
      case CONS_PRIMARY_KEY:
         printf("Primary Key");
         break;
      case CONS_UNIQUE:
         printf("Unique");
         break;
      case CONS_FOREIGN_KEY:
         printf("Foreign key (%s, %s)", constraint->constraint.ref.table_name, 
                                          constraint->constraint.ref.table_col_name);
         break;
      case CONS_AUTO_INCREMENT:
         printf("Auto increment");
         break;
      case CONS_NOT_NULL:
         printf("Not null");
         break;
      case CONS_CHECK:
         printf("Check: ");
         printCondition(constraint->constraint.check);
         break;
      default:
         printf("Unknown constraint type");
   }
}

ChiTable *add_foreign_key(ChiTable *table, ForeignKeyReference fkr) {
   if (table != NULL) {
      /* find the column that matches the cname given, and add this reference */
      ChiColumn *col = table->columns;
      for (; col; col=col->next) {
         if (!strcmp(col->name, fkr.col_name)) {
            add_constraints(col, ForeignKey(fkr));
            return table;
         }
      }
      fprintf(stderr, "Error: column %s not in table\n", fkr.col_name);
      return table;
   }
   fprintf(stderr, "Error: table is null\n");
   return table;
}

ChiTable *add_key_decs(ChiTable *table, KeyDec *decs) {
   StrList *slist;
   for (; decs; decs = decs->next) {
      switch (decs->t) {
         case KEY_DEC_PRIMARY:
            for (slist = decs->dec.primary_keys; slist; slist = slist->next) {
               if (!add_primary_key(table, slist->str))
                  fprintf(stderr, "Error: column '%s' not found\n", slist->str);
            }
            break;
         case KEY_DEC_FOREIGN:
            if (!add_foreign_key(table, decs->dec.fkey))
               fprintf(stderr, "Error: column '%s' not found\n", decs->dec.fkey.col_name);
            break;
         default:
            fprintf(stderr, "Unknown declaration type\n");
      }
   }
   return table;
}

KeyDec *ForeignKeyDec(ForeignKeyReference fkr) {
   KeyDec *kdec = (KeyDec *)calloc(1, sizeof(KeyDec));
   kdec->t = KEY_DEC_FOREIGN;
   kdec->dec.fkey = fkr;
   return kdec;
}
KeyDec *PrimaryKeyDec(StrList *col_names) {
   KeyDec *kdec = (KeyDec *)calloc(1, sizeof(KeyDec));
   kdec->t = KEY_DEC_PRIMARY;
   kdec->dec.primary_keys = col_names;
   return kdec;
}

ChiTable *CreateTable(const char *name, ChiColumn *columns, KeyDec *decs) {
   ChiTable *new_table = (ChiTable *)calloc(1, sizeof(ChiTable));
   new_table->name = strdup(name);
   new_table->columns = columns;
   return add_key_decs(new_table, decs);
}

static ChiTable *add_primary_key(ChiTable *table, const char *col_name) {
   ChiColumn *col = table->columns;
   for (; col; col = col->next) {
      if (!strcmp(col->name, col_name)) {
         add_constraints(col, PrimaryKey());
         return table;
      }
   }
   return NULL;
}

ChiTable *add_primary_keys(ChiTable *table, vector_t *col_names) {
   unsigned i;
   for (i=0; i < vector_size(col_names); ++i) {
      const char *col_name = (const char *)vector_getAt(col_names, i);
      table = add_primary_key(table, col_name);
      if (!table) {
         fprintf(stderr, "Error: column '%s' not found\n", col_name);
         return NULL;
      }
   }
   return table;
}

void deleteCreate(ChiTable *table) {
   deleteColumns(table->columns);
   free(table->name);
   free(table);
}

void printTable(ChiTable *table) {
   ChiColumn *col = table->columns;
   int first = 1, count = 0;
   char buf[100];
   printf("Table %s (\n", table->name);
   for (; col; col = col->next) {
      if (first) first = 0; else printf(",\n");
      printf("\t%s %s", col->name, typeToString(col->type, buf));
      printConstraints(col->constraints);
      if (++count == 10) break;
   }
   printf("\n)\n");
}

void add_table(ChiTable *table) {
   if (tables == NULL) 
      tables = vector_withData(1, table);
   else
      tables = vector_push(tables, table);
   printf("Added a new table:\n");
   printTable(table);
   printf("Now have %lu tables total\n", vector_size(tables));
}

KeyDec *append_key_dec(KeyDec *decs, KeyDec *dec) {
   decs->next = dec;
   return decs;
}

ChiColumn *append_column(ChiColumn *columns, ChiColumn *column) {
   columns->next = column;
   return columns;
}