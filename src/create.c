#include "../include/create.h"
#include "../include/ra.h"

vector_t *tables = NULL;
static Table_t *Table_addPrimaryKey(Table_t *table, const char *col_name);

Table_t *Table_addForeignKey(Table_t *table, ForeignKeyRef_t fkr) {
   if (table != NULL) {
      /* find the column that matches the cname given, and add this reference */
      Column_t *col = table->columns;
      for (; col; col=col->next) {
         if (!strcmp(col->name, fkr.col_name)) {
            Column_addConstraint(col, ForeignKey(fkr));
            return table;
         }
      }
      fprintf(stderr, "Error: column %s not in table\n", fkr.col_name);
      return table;
   }
   fprintf(stderr, "Error: table is null\n");
   return table;
}

Table_t *Table_addKeyDecs(Table_t *table, KeyDec_t *decs) {
   StrList_t *slist;
   for (; decs; decs = decs->next) {
      switch (decs->t) {
         case KEY_DEC_PRIMARY:
            for (slist = decs->dec.primary_keys; slist; slist = slist->next) {
               if (!Table_addPrimaryKey(table, slist->str))
                  fprintf(stderr, "Error: column '%s' not found\n", slist->str);
            }
            break;
         case KEY_DEC_FOREIGN:
            if (!Table_addForeignKey(table, decs->dec.fkey))
               fprintf(stderr, "Error: column '%s' not found\n", decs->dec.fkey.col_name);
            break;
         default:
            fprintf(stderr, "Unknown declaration type\n");
      }
   }
   return table;
}

KeyDec_t *ForeignKeyDec(ForeignKeyRef_t fkr) {
   KeyDec_t *kdec = (KeyDec_t *)calloc(1, sizeof(KeyDec_t));
   kdec->t = KEY_DEC_FOREIGN;
   kdec->dec.fkey = fkr;
   return kdec;
}
KeyDec_t *PrimaryKeyDec(StrList_t *col_names) {
   KeyDec_t *kdec = (KeyDec_t *)calloc(1, sizeof(KeyDec_t));
   kdec->t = KEY_DEC_PRIMARY;
   kdec->dec.primary_keys = col_names;
   return kdec;
}

Table_t *Table_make(const char *name, Column_t *columns, KeyDec_t *decs) {
   Table_t *new_table = (Table_t *)calloc(1, sizeof(Table_t));
   new_table->name = strdup(name);
   new_table->columns = columns;
   return Table_addKeyDecs(new_table, decs);
}

static Table_t *Table_addPrimaryKey(Table_t *table, const char *col_name) {
   Column_t *col = table->columns;
   for (; col; col = col->next) {
      if (!strcmp(col->name, col_name)) {
         Column_addConstraint(col, PrimaryKey());
         return table;
      }
   }
   return NULL;
}

Table_t *Table_addPrimaryKeys(Table_t *table, vector_t *col_names) {
   unsigned i;
   for (i=0; i < vector_size(col_names); ++i) {
      const char *col_name = (const char *)vector_getAt(col_names, i);
      table = Table_addPrimaryKey(table, col_name);
      if (!table) {
         fprintf(stderr, "Error: column '%s' not found\n", col_name);
         return NULL;
      }
   }
   return table;
}

void Table_delete(Table_t *table) {
   Column_deleteList(table->columns);
   free(table->name);
   free(table);
}

void Table_print(Table_t *table) {
   Column_t *col = table->columns;
   int first = 1, count = 0;
   char buf[100];
   printf("Table %s (\n", table->name);
   for (; col; col = col->next) {
      if (first) first = 0; else printf(",\n");
      printf("\t%s %s", col->name, typeToString(col->type, buf));
      Constraint_printList(col->constraints);
      if (++count == 10) break;
   }
   printf("\n)\n");
}

void add_table(Table_t *table) {
   if (tables == NULL) 
      tables = vector_withData(1, table);
   else
      tables = vector_push(tables, table);
}

KeyDec_t *KeyDec_append(KeyDec_t *decs, KeyDec_t *dec) {
   decs->next = dec;
   return decs;
}

TableReference_t *TableReference_make(char *table_name, char *alias) {
   TableReference_t *ref = (TableReference_t *)calloc(1, sizeof(TableReference_t));
   ref->table_name = table_name;
   ref->alias = alias;
   return ref;
}