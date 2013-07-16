#ifndef __CREATE_H_
#define __CREATE_H_

#include "common.h"
#include "column.h"

typedef struct Table_t {
   char *name;
   Column_t *columns;
} Table_t;

enum key_dec_type {KEY_DEC_PRIMARY, KEY_DEC_FOREIGN};

typedef struct KeyDec_t {
   enum key_dec_type t; 
   union {
      StrList_t *primary_keys;
      ForeignKeyRef_t fkey;
   } dec;
   struct KeyDec_t *next;
} KeyDec_t;

Table_t *Table_make(const char *name, Column_t *columns, KeyDec_t *decs);

/* setting primary and foreign keys outside of columns */
Table_t *Table_addKeyDecs(Table_t *table, KeyDec_t *decs);
KeyDec_t *KeyDec_append(KeyDec_t *decs, KeyDec_t *dec);
KeyDec_t *ForeignKeyDec(ForeignKeyRef_t fkr);
KeyDec_t *PrimaryKeyDec(StrList_t *col_names);

void Table_print(Table_t *table);

void Table_delete(Table_t *table);

void add_table(Table_t *table);

#endif