#ifndef __MOCK_DB_H__
#define __MOCK_DB_H__

#include "common.h"
#include "create.h"

void mock_db_init(void);
void add_table(Table_t *table);
void remove_table(Table_t *table);
Table_t *table_by_name(const char *name);
void show_tables(void);

#endif