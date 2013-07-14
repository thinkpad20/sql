#ifndef __DELETE_H_
#define __DELETE_H_

#include "common.h"

typedef struct ChiDelete {
   RA *ra;
   Condition *where;
} ChiDelete;

ChiDelete *Delete(RA *ra, Condition *where);

void deleteChiDelete(ChiDelete *del);

#endif