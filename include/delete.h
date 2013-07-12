#ifndef __DELETE_H_
#define __DELETE_H_

#include "common.h"

typedef struct Delete {
   RA *ra;
   Condition *where;
} Delete;

Delete *_Delete(RA *ra, Condition *where);

void deleteDelete(Delete *del);
#endif