#ifndef __INSERT_H_
#define __INSERT_H_ 

#include "common.h"

typedef struct Data {
   enum data_type t;
   union {
      int Int;
      double Double;
      char Char;
      char *Varchar;
      char *Text;
   } data;
} Data;

typedef struct Insert {
   RA *ra;
   unsigned num_data;
   Data **data;
} Insert;

Data *Int(int i);
Data *Char(char c);
Data *Varchar(const char *str);
Data *Text(const char *str);

Insert *_Insert(RA *ra, unsigned num_data, ...);

#endif