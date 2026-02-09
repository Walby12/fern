#ifndef VM_H
#define VM_H

#include <stddef.h>

typedef struct SymbolTable SymbolTable;

typedef struct Vm {
  char *src;
  size_t index;
  const char *cur_word; 
} Vm;

void trim(char *str);
Vm *init_vm(const char *file_name);
void vm_end(Vm *vm);
char *vm_get_next_tok(char **cursor);
void unescape_str(char *str);
void vm_parse(Vm *vm, SymbolTable *st);
void vm_parse_func_call(char **cursor, SymbolTable *st);
void vm_parse_print(char **cursor, SymbolTable *st);
void vm_parse_bind(char **cursor, SymbolTable *st);

#endif
