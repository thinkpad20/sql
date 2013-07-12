#ifndef __CREATE_H_
#define __CREATE_H_

#include "common.h"

typedef struct Column {
   char *name;
   enum data_type type;
} Column_t;

typedef struct Create {
   char *name;
   unsigned num_cols;
   Column_t **columns;
   Column_t *primary_key;
} Create_t;

Column_t *Column(const char *name, enum data_type type);
Create_t *Create(const char *name, unsigned num_cols, ...);
void deleteColumn(Column_t *column);
void deleteCreate(Create_t *create);

#endif