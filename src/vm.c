#include "vm.h"

#include <stdlib.h>
#include <stdio.h>

Vm *init_vm(const char *file_name) {
    Vm *vm = malloc(sizeof(Vm));
  
    FILE *f = fopen(file_name, "rb");
    if (f == NULL) {
      printf("ERROR: Could not open file: %s\n", file_name);
      exit(1);
    } 

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    vm->src = malloc(fsize + 1);
    fread(vm->src, fsize, 1, f);
    vm->src[fsize] = '\0';
    
    fclose(f);

    vm->index = 0;
       
    return vm;
}

void vm_end(Vm *vm) {
    free(vm->src);
    free(vm);
}
