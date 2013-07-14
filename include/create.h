#ifndef __CREATE_H_
#define __CREATE_H_

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
      LiteralVal *default_val;
      Condition *check;
   } constraint;
   struct Constraint *next;
} Constraint;

typedef struct ChiColumn {
   char *name;
   enum data_type type;
   size_t num_constraints;
   Constraint *constraints;
   struct ChiColumn *next;
} ChiColumn;

typedef struct ChiTable {
   char *name;
   ChiColumn *columns;
} ChiTable;

enum key_dec_type {KEY_DEC_PRIMARY, KEY_DEC_FOREIGN};

typedef struct KeyDec {
   enum key_dec_type t; 
   union {
      StrList *primary_keys;
      ForeignKeyReference fkey;
   } dec;
   struct KeyDec *next;
} KeyDec;

ChiTable *CreateTable(const char *name, ChiColumn *columns, KeyDec *decs);

/* setting primary and foreign keys outside of columns */
ChiTable *add_key_decs(ChiTable *table, KeyDec *decs);
KeyDec *append_key_dec(KeyDec *decs, KeyDec *dec);
KeyDec *ForeignKeyDec(ForeignKeyReference fkr);
KeyDec *PrimaryKeyDec(StrList *col_names);

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
Constraint *append_constraint(Constraint *constraints, Constraint *constraint);
ChiColumn *Column(const char *name, enum data_type type, Constraint *constraints);
ChiColumn *append_column(ChiColumn *columns, ChiColumn *column);
void printConstraint(void *constraint);
void printConstraints(Constraint *constraints);
void printTable(ChiTable *table);

void deleteTable(ChiTable *table);

extern vector_t *tables;

void add_table(ChiTable *table);

#endif