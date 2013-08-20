#ifndef __MOCK_DB_H__
#define __MOCK_DB_H__

#include "common.h"
#include "create.h"
#include "list.h"

void mock_db_init(void);
void add_table(Table_t *table);
void remove_table(Table_t *table);
Table_t *table_by_name(const char *name);
void show_tables(void);
List_t column_list(const char *table_name);
List_t columns_in_common(const char *table1, const char *table2);

#endif