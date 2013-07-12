#include "insert.h"

Data *Int(int i) {
   Data *new_data = (Data *)malloc(sizeof(Data));
   new_data->t = TYPE_INT;
   new_data->data.Int = i;
   return new_data;
}

Data *Char(char c) {
   Data *new_data = (Data *)malloc(sizeof(Data));
   new_data->t = TYPE_CHAR;
   new_data->data.Char = c;
   return new_data;
}

Data *Varchar(const char *str) {
   Data *new_data = (Data *)malloc(sizeof(Data));
   new_data->t = TYPE_VARCHAR;
   new_data->data.Varchar = strdup(str);
   return new_data;
}

Data *Text(const char *str) {
   Data *new_data = (Data *)malloc(sizeof(Data));
   new_data->t = TYPE_TEXT;
   new_data->data.Text = strdup(str);
   return new_data;
}

Insert *_Insert(RA *ra, unsigned num_data, ...) {
   Insert *new_insert = (Insert *)malloc(sizeof(Insert));
   va_list argp;
   int i, j=0;
   va_start(argp, num_data);
   new_insert->ra = ra;
   new_insert->num_data = num_data;
   if (num_data > 0) 
      new_insert->data = malloc(num_data * sizeof(Data));
   for (i=0; i<num_data; ++i) {
      new_insert->data[j++] = va_arg(argp, Data *);
   }
   return new_insert;
}