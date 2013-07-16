#include "../include/column.h"
#include "../include/condition.h"

static ssize_t size_constraint = -1;

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

Constraint *Default(LiteralVal *val) {
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

Constraint *ColumnSize(unsigned size) {
   Constraint *con = (Constraint *)calloc(1, sizeof(Constraint));
   con->t = CONS_SIZE;
   con->constraint.size = size;
   return con;
}

static void deleteConstraints(Constraint *constraint) {
   if (constraint) {
      Constraint *next = constraint->next;
      switch (constraint->t) {
         case CONS_DEFAULT:
            deleteLiteralVal(constraint->constraint.default_val);
            break;
         case CONS_CHECK:
            deleteCondition(constraint->constraint.check);
            break;
         default:
            break;
      }
      deleteConstraints(next);
   }
}

void deleteColumns(ChiColumn *column) {
   if (column) {
      ChiColumn *next = column->next;
      free(column->name);
      deleteConstraints(column->constraints);
      free(column);
      deleteColumns(next);
   }
}

void printConstraints(Constraint *constraints) {
   int first = 1;
   if (constraints) {
      printf(" [");
      for (; constraints; constraints = constraints->next) {
         if (first) {
            first = 0;
         } else {
            printf(", ");
         }
         printConstraint(constraints);
      }
      printf("]");
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

ChiColumn *Column(const char *name, enum data_type type, Constraint *constraints) {
   ChiColumn *new_column = (ChiColumn *)calloc(1, sizeof(ChiColumn));
   new_column->name = strdup(name);
   new_column->type = type;
   new_column->constraints = constraints;
   /* if the parser found a size constraint, then size_constraitn will be > 0 */
   if (size_constraint > 0) {
      append_constraint(new_column->constraints, ColumnSize(size_constraint));
      size_constraint = -1;
   }
   return new_column;
}

ChiColumn *add_constraints(ChiColumn *column, Constraint *constraints) {
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
      case CONS_SIZE:
         printf("Size: %u", constraint->constraint.size);
         break;
      default:
         printf("Unknown constraint type");
   }
}

void set_size(ssize_t size) {
   size_constraint = size;
}

static ChiColumn *app_col(ChiColumn *col1, ChiColumn *col2) {
   col1->next = col2;
   return col1;
}

ChiColumn *append_column(ChiColumn *col1, ChiColumn *col2) {
   if (!col1) return col2;
   return app_col(col1, append_column(col1->next, col2));
}

ColumnReference *makeColumnReference(const char *tname, const char *cname) {
   ColumnReference *ref = (ColumnReference *)calloc(1, sizeof(ColumnReference));
   if (tname) ref->tableName = strdup(tname);
   if (cname) ref->columnName = strdup(cname);
   return ref;
}