#ifndef __CREATE_H_
#define __CREATE_H_

#include "common.h"
#include "column.h"

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

void printTable(ChiTable *table);

void deleteTable(ChiTable *table);

void add_table(ChiTable *table);

#endif