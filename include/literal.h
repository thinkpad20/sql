#ifndef __LITERAL_H_
#define __LITERAL_H_

#include "common.h"

union LitVal {
   int ival;
   double dval;
   char cval;
   char *strval;
};

typedef struct LiteralVal {
   enum data_type t;
   union LitVal val;
   struct LiteralVal *next; /* linked list */
} LiteralVal;

LiteralVal makeLiteralVal(enum data_type type, union LitVal val);

LiteralVal *litInt(int i);
LiteralVal *litDouble(double d);
LiteralVal *litChar(char c);
LiteralVal *litText(char *str);
LiteralVal *appendLiteralVal(LiteralVal *val, LiteralVal *toAppend);

void deleteLiteralVal(LiteralVal *lval);

void printLiteralVal(LiteralVal *val);

#endif