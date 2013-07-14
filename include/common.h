#ifndef __COMMON_H_
#define __COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "vector.h"
#include "list.h"

/* Forward declarations */
typedef struct RA RA;
typedef struct Condition Condition;

enum data_type {
   TYPE_INT,
   TYPE_DOUBLE,
   TYPE_CHAR,
   TYPE_TEXT
};

typedef struct StrList {
   char *str;
   struct StrList *next;
} StrList;

char *typeToString(enum data_type type, char *buf);
StrList *strlist(const char *str, StrList *next);

#endif