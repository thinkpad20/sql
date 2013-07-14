#include "../include/common.h"

char *typeToString(enum data_type type, char *buf) {
   switch (type) {
      case TYPE_INT:
         sprintf(buf, "int");
         break;
      case TYPE_DOUBLE:
         sprintf(buf, "double");
         break;
      case TYPE_CHAR:
         sprintf(buf, "char");
         break;
      case TYPE_TEXT:
         sprintf(buf, "text");
         break;
   }
   return buf;
}

StrList *strlist(const char *str, StrList *next) {
   StrList *list = (StrList *)calloc(1, sizeof(StrList));
   list->str = strdup(str);
   list->next = next;
   return list;
}