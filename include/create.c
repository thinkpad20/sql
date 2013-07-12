#include "../include/create.h"

Column_t *Column(const char *name, enum data_type type) {
   Column_t *new_column = (Column_t *)calloc(1, sizeof(Column_t));
   new_column->name = strdup(name);
   new_column->type = type;
   return new_column;
}
Create_t *Create(const char *name, unsigned num_cols, ...) {
   va_list argp;
   int i;
   Create_t *new_create = (Create_t *)calloc(1, sizeof(Create_t));
   new_create->name = strdup(name);
   new_create->num_cols = num_cols;
   va_start(argp, num_cols);
   if (num_cols > 0)
      new_create->columns = (Column_t **)calloc(num_cols, sizeof(Column_t));
   for (i = 0; i<num_cols; ++i)
      new_create->columns[i] = va_arg(argp, Column_t *);
   return new_create;
}

Create_t *add_primary_key(Create_t *create, const char *col_name) {
   int i;
   for (i=0; i<create->num_cols; ++i) {
      if (!strcmp(create->columns[i]->name, col_name)) {
         create->primary_key = create->columns[i];
         return create;
      }
   }
   return NULL;
}

void deleteColumn(Column_t *column) {
   free(column->name);
   free(column);
}

void deleteCreate(Create_t *create) {
   int i;
   for (i = 0; i<create->num_cols; ++i)
      deleteColumn(create->columns[i]);
   free(create->name);
   free(create);
}
