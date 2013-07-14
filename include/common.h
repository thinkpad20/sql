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
   TYPE_VARCHAR, 
   TYPE_TEXT
};

#endif