#ifndef VM_H
#define VM_H

#include <stddef.h>

typedef struct Vm {
  char *src;
  size_t index;
  const char *cur_word; 
} Vm;

void trim(char *str);
Vm *init_vm(const char *file_name);
void vm_end(Vm *vm);
void vm_parse(Vm *vm);
void vm_parse_func_call();
void vm_parse_print();

#endif
