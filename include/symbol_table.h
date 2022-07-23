#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "klib/khash.h"
#include "vec/vec.h"

typedef vec_t(struct symbol*) param;
typedef struct symbol
{
    char* identifier;
    int value;
    int scope; 
    struct symbol* next;
    int is_hidden;
    int is_function;
    int is_constant;
    param params;
    int data_type;
}*sym_ptr, sym;

KHASH_MAP_INIT_STR(symbol_table, sym_ptr);

void init_symbol_table();
int insert_symbol_table(char* id, int dt_type, int val, int is_function);
sym_ptr lookup_symbol_table(char* id, int scope);
void increment_scope();
void decrement_scope();
int get_scope();
void dump_symbol_table();
void close_symbol_table();

#endif