#include "../include/literal.h"

LiteralVal makeLiteralVal(enum data_type type, union LitVal val) {
   LiteralVal lval;
   lval.t = type;
   lval.val = val;
   return lval;
}

LiteralVal *litInt(int i) {
   LiteralVal *lval = (LiteralVal *)calloc(1, sizeof(LiteralVal));
   lval->t = TYPE_INT;
   lval->val.ival = i;
   return lval;
}

LiteralVal *litDouble(double d) {
   LiteralVal *lval = (LiteralVal *)calloc(1, sizeof(LiteralVal));
   lval->t = TYPE_DOUBLE;
   lval->val.dval = d;
   return lval;
}

LiteralVal *litChar(char c) {
   LiteralVal *lval = (LiteralVal *)calloc(1, sizeof(LiteralVal));
   lval->t = TYPE_CHAR;
   lval->val.cval = c;
   return lval;
}

LiteralVal *litText(char *str) {
   LiteralVal *lval = (LiteralVal *)calloc(1, sizeof(LiteralVal));
   lval->t = TYPE_TEXT;
   lval->val.strval = str;
   return lval;
}

void printLiteralVal(LiteralVal *val) {
   char buf[100];
   printf("%s ", typeToString(val->t, buf));
   switch (val->t) {
      case TYPE_INT:
         printf("%d", val->val.ival);
         break;
      case TYPE_DOUBLE:
         printf("%f", val->val.dval);
         break;
      case TYPE_CHAR:
         printf("%c", val->val.cval);
         break;
      case TYPE_TEXT:
         printf("%s", val->val.strval);
         break;
      default:
         printf("(unknown type)");
   }
}

LiteralVal *appendLiteralVal(LiteralVal *val, LiteralVal *toAppend) {
   val->next = toAppend;
   return val;
}

void deleteLiteralVal(LiteralVal *lval) {
   if (lval->t == TYPE_TEXT)
      free(lval->val.strval);
   free(lval);
}