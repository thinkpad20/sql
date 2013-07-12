#include "../include/delete.h"
#include "../include/ra.h"

Delete *_Delete(RA *ra, Condition *where) {
   Delete *new_delete = (Delete *)calloc(1, sizeof(Delete));
   new_delete->ra = ra;
   new_delete->where = where;
   return new_delete;
}

void deleteDelete(Delete *del) {
   deleteCondition(del->where);
   deleteRA(del->ra);
   free(del);
}