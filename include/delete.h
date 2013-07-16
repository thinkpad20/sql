#ifndef __DELETE_H_
#define __DELETE_H_

#include "common.h"

typedef struct ChiDelete {
   char *table_name;
   Condition *where;
} ChiDelete;

ChiDelete *makeDelete(const char *table_name, Condition *where);
void deleteDelete(ChiDelete *del);
void printDelete(ChiDelete *del);

#endif