#ifndef __COLUMN_H_
#define __COLUMN_H_

#include "common.h"
#include "literal.h"

enum constraint_type {
   CONS_NOT_NULL,
   CONS_UNIQUE,
   CONS_PRIMARY_KEY,
   CONS_FOREIGN_KEY,
   CONS_DEFAULT,
   CONS_AUTO_INCREMENT,
   CONS_CHECK,
   CONS_SIZE,
};

typedef struct ForeignKeyReference {
   const char *col_name, *table_name, *table_col_name;
} ForeignKeyReference;

typedef struct Constraint {
   enum constraint_type t;
   union {
      ForeignKeyReference ref;
      LiteralVal *default_val;
      unsigned size;
      Condition *check;
   } constraint;
   struct Constraint *next;
} Constraint;

typedef struct ChiColumn {
   char *name;
   enum data_type type;
   Constraint *constraints;
   struct ChiColumn *next;
} ChiColumn;

typedef struct ColumnReference {
   char *tableName, *columnName, *columnAlias;
} ColumnReference;

/* constraints on single columns */
ForeignKeyReference makeFullFKeyReference(const char *cname, ForeignKeyReference fkey);
ForeignKeyReference makeFKeyReference(const char *foreign_tname,
                                      const char *foreign_cname);

Constraint *NotNull(void);
Constraint *AutoIncrement(void);
Constraint *PrimaryKey(void);
Constraint *ForeignKey(ForeignKeyReference fkr);
Constraint *Default(LiteralVal *val);
Constraint *Unique(void);
Constraint *Check(Condition *cond);
Constraint *ColumnSize(unsigned size);
Constraint *append_constraint(Constraint *constraints, Constraint *constraint);
ChiColumn *add_constraints(ChiColumn *column, Constraint *constraints);
ChiColumn *Column(const char *name, enum data_type type, Constraint *constraints);
ChiColumn *append_column(ChiColumn *columns, ChiColumn *column);

ColumnReference *makeColumnReference(const char *, const char *);

void printConstraint(void *constraint);
void printConstraints(Constraint *constraints);
void deleteColumns(ChiColumn *column);

/* sets the size of the next column */
void set_size(ssize_t size);

#endif