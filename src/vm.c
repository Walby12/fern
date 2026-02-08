#include "vm.h"
#include "comp.h"

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

char* vm_get_next_tok(char **cursor) {
    char *start = *cursor;
    
    while (**cursor && isspace(**cursor)) (*cursor)++;
    
    if (**cursor == '\0') return NULL;
    start = *cursor;
    
    if (**cursor == '"') {
        (*cursor)++;
        start = *cursor;
        
        while (**cursor && **cursor != '"') {
            (*cursor)++;
        }
        
        if (**cursor == '"') {
            **cursor = '\0';
            (*cursor)++;
        }
    } else {
        while (**cursor && !isspace(**cursor)) {
            (*cursor)++;
        }
        
        if (**cursor != '\0') {
            **cursor = '\0';
            (*cursor)++;
        }
    }
    
    return start;
}

void unescape_str(char *str) {
    char *src = str;
    char *dst = str;

    while (*src) {
        if (*src == '\\' && *(src + 1) == 'n') {
            *dst = '\n';
            src += 2;
        } else if (*src == '\\' && *(src + 1) == '\\') {
            *dst = '\\';
            src += 2;
        } else {
            *dst = *src;
            src++;
        }
        dst++;
    }
    *dst = '\0';
}

void vm_parse(Vm *vm) {
    char *cursor = vm->src;
    char *token = vm_get_next_tok(&cursor);

    while (token != NULL) {
        if (strcmp(token, "func_call") == 0) {
            vm_parse_func_call(&cursor);
        } else {
            printf("ERROR: Unknow stmt in ir: '%s'\n", token);
        }
        token = vm_get_next_tok(&cursor);
    }
    if (verbose) printf("\nFinished interpreting ir\n");
}

void vm_parse_func_call(char **cursor) {
    char *arg = vm_get_next_tok(cursor);

    if (arg != NULL) {
        if (strcmp(arg, "print") == 0) {
            vm_parse_print(cursor);
        } else {
            printf("ERROR: Unknow func_call arg: '%s'\n", arg);
        }
    } else {
        printf("ERROR: func_call must take an arg\n");
        exit(1);
    }
}

void vm_parse_print(char **cursor) {
    char *arg = vm_get_next_tok(cursor);
    unescape_str(arg);
    printf("%s", arg);
}
