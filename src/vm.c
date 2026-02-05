#include "vm.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void trim(char *str) {
    if (str == NULL) return;

    char *start = str;
    while (isspace((unsigned char)*start)) {
        start++;
    }

    char *end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }

   *(end + 1) = '\0';

    if (start != str) {
        memmove(str, start, strlen(start) + 1);
    }
}

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

void vm_parse(Vm *vm) {
    char *token = strtok(vm->src, " ");

    while (token != NULL) {
        trim(token);
        if (strcmp(token, "func_call") == 0) {
            vm_parse_func_call();
        } else {
            printf("ERROR: Unknow stmt in ir: '%s'\n", token);
        }
        token = strtok(NULL, " ");
    }
    printf("Finished interpreting ir\n");
}

void vm_parse_func_call() {
    char *arg = strtok(NULL, " ");

    if (arg != NULL) {
        trim(arg);
        if (strcmp(arg, "print") == 0) {
            vm_parse_print();
        } else {
            printf("ERROR: Unknow func_call arg: '%s'\n", arg);
        }
    } else {
        printf("ERROR: func_call must take an arg\n");
        exit(1);
    }
}

void vm_parse_print() {
    printf("Hello world\n");
}
