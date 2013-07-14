#ifndef __CREATE_H_
#define __CREATE_H_

#include "common.h"

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

union LitVal {
   int ival;
   double dval;
   char cval;
   char *strval;
};

typedef struct LiteralVal {
   enum data_type t;
   union LitVal val;
} LiteralVal;

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
   unsigned num_constraints;
   Constraint **constraints;
} ChiColumn;

typedef struct ChiTable {
   char *name;
   unsigned num_cols, num_primary_keys, num_foreign_keys;
   ChiColumn **columns;
   unsigned *primary_keys;
} ChiTable;

enum key_dec_type {KEY_DEC_PRIMARY, KEY_DEC_FOREIGN};

typedef struct KeyDec {
   enum key_dec_type t; 
   union {
      vector_t *primary_keys;
      ForeignKeyReference fkey;
   } dec;
} KeyDec;

ChiTable *CreateTable(const char *name, unsigned num_cols, ...);
ChiTable *CreateTableFromVector(const char *name, vector_t *vec);

/* setting primary and foreign keys outside of columns */
ChiTable *add_key_decs(ChiTable *table, vector_t *decs);
vector_t *append_key_dec(vector_t *decs, KeyDec *dec);
KeyDec *ForeignKeyDec(ForeignKeyReference fkr);
KeyDec *PrimaryKeyDec(vector_t *col_names);

/* constraints on single columns */
ForeignKeyReference makeFullFKeyReference(const char *cname, ForeignKeyReference fkey);
ForeignKeyReference makeFKeyReference(const char *foreign_tname,
                                      const char *foreign_cname);
LiteralVal makeLiteralVal(enum data_type type, union LitVal val);
Constraint *NotNull(void);
Constraint *AutoIncrement(void);
Constraint *PrimaryKey(void);
Constraint *ForeignKey(ForeignKeyReference fkr);
Constraint *Default(LiteralVal val);
Constraint *Unique(void);
Constraint *Check(Condition *cond);
vector_t *append_constraint(vector_t *constraints, Constraint *constraint);
ChiColumn *add_constraints(ChiColumn *column, vector_t *constraints);
ChiColumn *add_constraint(ChiColumn *column, Constraint *constraints);
ChiColumn *Column(const char *name, enum data_type type);
void printConstraint(void *constraint);
void printConstraints(vector_t *constraints);
void printTable(ChiTable *table);

void deleteColumn(ChiColumn *column);
void deleteTable(ChiTable *table);

extern vector_t *tables;

void add_table(ChiTable *table);

#endif