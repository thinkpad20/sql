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
};

typedef struct ForeignKeyReference {
   const char *col_name, *table_name, *table_col_name;
} ForeignKeyReference;

typedef struct Constraint {
   enum constraint_type t;
   union {
      ForeignKeyReference ref;
      LiteralVal default_val;
      Condition *check;
   } constraint;
} Constraint;

typedef struct ChiColumn {
   char *name;
   enum data_type type;
   size_t num_constraints;
   Constraint **constraints;
   ChiColumn *next;
} ChiColumn;