#include "../include/delete.h"
#include "../include/ra.h"

ChiDelete *makeDelete(const char *table_name, Condition *where) {
   ChiDelete *new_delete = (ChiDelete *)calloc(1, sizeof(ChiDelete));
   new_delete->table_name = strdup(table_name);
   new_delete->where = where;
   return new_delete;
}

void deleteDelete(ChiDelete *del) {
   deleteCondition(del->where);
   free(del->table_name);
   free(del);
}

void printDelete(ChiDelete *del) {
   printf("Delete from %s where ", del->table_name);
   printCondition(del->where);
}