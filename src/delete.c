#include "../include/delete.h"
#include "../include/ra.h"

ChiDelete *makeDelete(const char *table_name, Condition_t *where) {
   ChiDelete *new_delete = (ChiDelete *)calloc(1, sizeof(ChiDelete));
   new_delete->table_name = strdup(table_name);
   new_delete->where = where;
   return new_delete;
}

void deleteDelete(ChiDelete *del) {
   Condition_delete(del->where);
   free(del->table_name);
   free(del);
}

void printDelete(ChiDelete *del) {
   printf("Delete from %s where ", del->table_name);
   Condition_print(del->where);
}