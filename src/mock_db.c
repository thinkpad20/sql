#include "../include/mock_db.h"
#include "../include/list.h"

static List_t tables;

static void print_table(void *table_ptr) {
   Table_print((Table_t *)table_ptr);
}

void mock_db_init() {
   puts("initializing..."); fflush(stdout);
   list_init(&tables, Table_free);
   list_setPrintFunc(&tables, print_table);
   puts("done..."); fflush(stdout);
}
void add_table(Table_t *table) {
   list_addBack(&tables, table);
}

void remove_table(Table_t *table) {
   list_removeByPointerFree(&tables, table);
}

static void toStringBuf (char *name, void *table) {
   strcpy(name, ((Table_t *)table)->name);
}

static char *toString (void *table) {
   return ((Table_t *)table)->name;
}

Table_t *table_by_name(const char *name) {
   return (Table_t *)list_findByString(&tables, toStringBuf, name);
}

void show_tables() {
   list_print(&tables, false);
}