#include "../include/create.h"
#include "../include/ra.h"

vector_t *tables = NULL;
static ChiTable *add_primary_key(ChiTable *table, const char *col_name);

ChiColumn *Column(const char *name, enum data_type type) {
   ChiColumn *new_column = (ChiColumn *)calloc(1, sizeof(ChiColumn));
   new_column->name = strdup(name);
   new_column->type = type;
   return new_column;
}

ChiColumn *add_constraints(ChiColumn *column, vector_t *constraints) {
   int i;
   /* if there are already some constraints, add them to the vector first */
   if (column->num_constraints > 0) {
      for (i=0; i<column->num_constraints; ++i)
         vector_push(constraints, column->constraints[i]);
      free(column->constraints);
   }
   column->num_constraints = vector_size(constraints);
   column->constraints = (Constraint **)calloc(vector_size(constraints), 
                                                sizeof(Constraint *));
   for (i=0; i<vector_size(constraints); ++i) {
      column->constraints[i] = (Constraint *)vector_getAt(constraints, i);
   }

   vector_free(constraints);
   return column;
}

LiteralVal makeLiteralVal(enum data_type type, union LitVal val) {
   LiteralVal lval;
   lval.t = type;
   lval.val = val;
   return lval;
}

vector_t *append_constraint(vector_t *constraints, Constraint *constraint) {
   if (constraints == NULL)
      constraints = vector_withData(1, constraint);
   else
      vector_push(constraints, constraint);
   return constraints;
}

void printConstraint(void *constraint_voidp) {
   Constraint *constraint = (Constraint *)constraint_voidp;
   switch(constraint->t) {
      case CONS_DEFAULT:
         printf("Default");
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

ForeignKeyReference makeFullFKeyReference(const char *cname, ForeignKeyReference fkey) {
   fkey.col_name = cname;
   return fkey;
}

ForeignKeyReference makeFKeyReference(const char *foreign_tname,
                                      const char *foreign_cname) {
   ForeignKeyReference fkey;
   fkey.col_name = NULL;
   fkey.table_name = foreign_tname;
   fkey.table_col_name = foreign_cname;
   return fkey;
}

ChiTable *add_foreign_key(ChiTable *table, ForeignKeyReference fkr) {
   if (table != NULL) {
      /* find the column that matches the cname given, and add this reference */
      unsigned i;
      for (i=0; i<table->num_cols; ++i) {
         if (!strcmp(table->columns[i]->name, fkr.col_name)) {
            add_constraint(table->columns[i], ForeignKey(fkr));
            return table;
         }
      }
      fprintf(stderr, "Error: column %s not in table\n", fkr.col_name);
      return table;
   }
   fprintf(stderr, "Error: table is null\n");
   return table;
}

void printConstraints(vector_t *constraints) {
   vector_print(constraints, printConstraint);
}

ChiTable *add_key_decs(ChiTable *table, vector_t *decs) {
   size_t i, j;
   for (i=0; i<vector_size(decs); ++i) {
      KeyDec *dec = (KeyDec *)vector_getAt(decs, i);
      switch (dec->t) {
         case KEY_DEC_PRIMARY:
            for (j=0; j<vector_size(dec->dec.primary_keys); ++j) {
               char *col = (char *)vector_getAt(dec->dec.primary_keys, j);
               if (!add_primary_key(table, col))
                  fprintf(stderr, "Error: column '%s' not found\n", col);
            }
            break;
         case KEY_DEC_FOREIGN:
            if (!add_foreign_key(table, dec->dec.fkey))
               fprintf(stderr, "Error: column '%s' not found\n", dec->dec.fkey.col_name);
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
KeyDec *PrimaryKeyDec(vector_t *col_names) {
   KeyDec *kdec = (KeyDec *)calloc(1, sizeof(KeyDec));
   kdec->t = KEY_DEC_PRIMARY;
   kdec->dec.primary_keys = col_names;
   return kdec;
}

ChiTable *CreateTable(const char *name, unsigned num_cols, ...) {
   va_list argp;
   int i;
   ChiTable *new_table = (ChiTable *)calloc(1, sizeof(ChiTable));
   new_table->name = strdup(name);
   new_table->num_cols = num_cols;
   va_start(argp, num_cols);
   if (num_cols > 0)
      new_table->columns = (ChiColumn **)calloc(num_cols, sizeof(ChiColumn));
   for (i = 0; i<num_cols; ++i)
      new_table->columns[i] = va_arg(argp, ChiColumn *);
   return new_table;
}

ChiTable *CreateTableFromVector(const char *name, vector_t *vec) {
   ChiTable *new_table = (ChiTable *)calloc(1, sizeof(ChiTable));
   int i;
   new_table->num_cols = vector_size(vec);
   if (vec->size > 0)
      new_table->columns = (ChiColumn **)calloc(vector_size(vec), sizeof(ChiColumn));
   for (i = 0; i < vector_size(vec); ++i) {
      new_table->columns[i] = vector_getAt(vec, i);
   }
   new_table->name = strdup(name);
   return new_table;
}

static ChiTable *add_primary_key(ChiTable *table, const char *col_name) {
   unsigned i;
   for (i=0; i<table->num_cols; ++i) {
      if (!strcmp(table->columns[i]->name, col_name)) {
         add_constraint(table->columns[i], PrimaryKey());
         return table;
      }
   }
   return NULL;
}

ChiColumn *add_constraint(ChiColumn *col, Constraint *constraint) {
   return add_constraints(col, vector_withData(1, constraint));
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

void deleteColumn(ChiColumn *column) {
   free(column->name);
   free(column);
}

void deleteCreate(ChiTable *table) {
   int i;
   for (i = 0; i<table->num_cols; ++i)
      deleteColumn(table->columns[i]);
   free(table->name);
   free(table);
}

Constraint *NotNull(void) {
   Constraint *con = (Constraint *)calloc(1, sizeof(Constraint));
   con->t = CONS_NOT_NULL;
   return con;
}

Constraint *AutoIncrement(void) {
   Constraint *con = (Constraint *)calloc(1, sizeof(Constraint));
   con->t = CONS_AUTO_INCREMENT;
   return con;
}

Constraint *PrimaryKey(void) {
   Constraint *con = (Constraint *)calloc(1, sizeof(Constraint));
   con->t = CONS_PRIMARY_KEY;
   return con;
}

Constraint *ForeignKey(ForeignKeyReference fkr) {
   Constraint *con = (Constraint *)calloc(1, sizeof(Constraint));
   con->t = CONS_FOREIGN_KEY;
   con->constraint.ref = fkr;
   return con;
}

Constraint *Default(LiteralVal val) {
   Constraint *con = (Constraint *)calloc(1, sizeof(Constraint));
   con->t = CONS_DEFAULT;
   con->constraint.default_val = val;
   return con;
}

Constraint *Unique(void) {
   Constraint *con = (Constraint *)calloc(1, sizeof(Constraint));
   con->t = CONS_UNIQUE;
   return con;
}

Constraint *Check(Condition *cond) {
   Constraint *con = (Constraint *)calloc(1, sizeof(Constraint));
   con->t = CONS_CHECK;
   con->constraint.check = cond;
   return con;
}

char *typeToString(enum data_type type, char *buf) {
   switch (type) {
      case TYPE_INT:
         sprintf(buf, "int");
         break;
      case TYPE_DOUBLE:
         sprintf(buf, "double");
         break;
      case TYPE_CHAR:
         sprintf(buf, "char");
         break;
      case TYPE_VARCHAR:
         sprintf(buf, "varchar");
         break;
      case TYPE_TEXT:
         sprintf(buf, "text");
         break;
   }
   return buf;
} 

void printTable(ChiTable *table) {
   unsigned i, j;
   char buf[100];
   printf("Table %s (\n", table->name);
   for (i=0; i<table->num_cols; ++i) {
      ChiColumn *col = table->columns[i];
      if (i != 0) printf(",\n");
      printf("\t%s %s", col->name, typeToString(col->type, buf));
      if (col->num_constraints > 0) {
         printf(" [");
         for (j=0; j<col->num_constraints; ++j) {
            if (j != 0) printf(", ");
            printConstraint(col->constraints[j]);
         }
         printf("]");
      }
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