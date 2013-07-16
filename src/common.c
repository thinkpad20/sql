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

StrList_t *strlist(const char *str, StrList_t *next) {
   StrList_t *list = (StrList_t *)calloc(1, sizeof(StrList_t));
   list->str = strdup(str);
   list->next = next;
   return list;
}