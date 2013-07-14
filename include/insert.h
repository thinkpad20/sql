#ifndef __INSERT_H_
#define __INSERT_H_ 

#include "common.h"
#include "create.h"

typedef struct ChiInsert {
   RA *ra;
   StrList *col_names;
   LiteralVal *values;
} ChiInsert;

ChiInsert *InsertInto(RA *ra, StrList *opt_col_names, LiteralVal *values);
void printInsert(ChiInsert *insert);

#endif