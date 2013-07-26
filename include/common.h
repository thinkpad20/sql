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
typedef struct Condition_t Condition_t;

enum data_type {
   TYPE_INT,
   TYPE_DOUBLE,
   TYPE_CHAR,
   TYPE_TEXT
};

typedef struct StrList_t {
   char *str;
   struct StrList_t *next;
} StrList_t;

char *typeToString(enum data_type type, char *buf);
StrList_t *StrList_makeWithNext(const char *str, StrList_t *next);
StrList_t *StrList_make(char *str);
StrList_t *StrList_append(StrList_t *list1, StrList_t *list2);
void StrList_print(StrList_t *list);
void upInd(void);
void downInd(void);
void indent_print(const char *format,...);

#endif
