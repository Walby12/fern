#ifndef VM_H
#define VM_H

#include <stddef.h>

typedef enum VmTok {
  VM_IDENT,
  VM_END_OF_FILE,
} VmTok;

typedef struct Vm {
  VmTok cur_tok;
  char *src;
  size_t index;
  const char *cur_word; 
} Vm;

Vm *init_vm(const char *file_name);
void vm_end(Vm *vm);

#endif
