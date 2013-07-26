#include "../include/delete.h"
#include "../include/ra.h"

Delete_t *Delete_make(const char *table_name, Condition_t *where) {
   Delete_t *new_delete = (Delete_t *)calloc(1, sizeof(Delete_t));
   new_delete->table_name = strdup(table_name);
   new_delete->where = where;
   return new_delete;
}

void deleteDelete(Delete_t *del) {
   Condition_delete(del->where);
   free(del->table_name);
   free(del);
}

void Delete_print(Delete_t *del) {
   printf("Delete from %s where ", del->table_name);
   Condition_print(del->where);
   puts("");
}
