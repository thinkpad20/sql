#include "../include/column.h"
#include "../include/condition.h"

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