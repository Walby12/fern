#include "vm.h"
#include "comp.h"
#include "vars.h"

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
    size_t read_count = fread(vm->src, 1, fsize, f);
    vm->src[read_count] = '\0';

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

void vm_parse(Vm *vm, SymbolTable *st) {
    char *cursor = vm->src;
    char *token = vm_get_next_tok(&cursor);

    while (token != NULL) {
        if (strcmp(token, "func_call") == 0) {
            vm_parse_func_call(&cursor, st);
        } else if (strcmp(token, "bind") == 0) {
            vm_parse_bind(&cursor, st);
        } else {
            printf("RUNTIME ERROR: Unknow stmt: '%s'\n", token);
            exit(1);
        }
        token = vm_get_next_tok(&cursor);
    }
    if (verbose) printf("\nFinished interpreting ir\n");
}

void vm_parse_func_call(char **cursor, SymbolTable *st) {
    char *arg = vm_get_next_tok(cursor);
    if (arg != NULL) {
        if (strcmp(arg, "print") == 0) {
            vm_parse_print_literal(cursor, VAR_STRING);
        } else if (strcmp(arg, "print_num") == 0) {
            vm_parse_print_literal(cursor, VAR_NUMBER);
        } else if (strcmp(arg, "print_str") == 0) {
            vm_parse_print_var(cursor, st, VAR_STRING);
        } else if (strcmp(arg, "print_int") == 0) {
            vm_parse_print_var(cursor, st, VAR_NUMBER);
        } else if (strcmp(arg, "print_int_as_str") == 0) {
            vm_parse_print_int_as_str(cursor, st);
        } else {
            printf("RUNTIME ERROR: Unknown func_call arg: '%s'\n", arg);
            exit(1);
        }
    } else {
        printf("RUNTIME ERROR: func_call must take an arg\n");
        exit(1);
    }
}

void vm_parse_print_int_as_str(char **cursor, SymbolTable *st) {
    char *arg = vm_get_next_tok(cursor);
    if (arg == NULL) {
        printf("RUNTIME ERROR: print expects an arg\n");
        exit(1);
    }
    
    Var *found = get_var(st, arg);
    if (!found) {
        printf("RUNTIME ERROR: Could not find var: %s\n", arg);
        exit(1);
    }
    
    if (found->type != VAR_NUMBER) {
        printf("RUNTIME ERROR: Type mismatch for var: %s\n", arg);
        exit(1);
    }
    
    printf("%d", found->as.number);
}

void vm_parse_print_literal(char **cursor, VarType type) {
    char *arg = vm_get_next_tok(cursor);
    if (arg == NULL) {
        printf("RUNTIME ERROR: print expects an arg\n");
        exit(1);
    }
    
    if (type == VAR_STRING) {
        unescape_str(arg);
        printf("%s", arg);
    } else if (type == VAR_NUMBER) {
        printf("%s", arg);
    }
}

void vm_parse_print_var(char **cursor, SymbolTable *st, VarType expected_type) {
    char *arg = vm_get_next_tok(cursor);
    if (arg == NULL) {
        printf("RUNTIME ERROR: print expects an arg\n");
        exit(1);
    }
    
    Var *found = get_var(st, arg);
    if (!found) {
        printf("RUNTIME ERROR: Could not find var: %s\n", arg);
        exit(1);
    }
    
    if (found->type != expected_type) {
        printf("RUNTIME ERROR: Type mismatch for var: %s\n", arg);
        exit(1);
    }
    
    if (expected_type == VAR_STRING) {
        printf("%s", found->as.string);
    } else if (expected_type == VAR_NUMBER) {
        printf("%d", found->as.number);
    }
}

void vm_parse_bind(char **cursor, SymbolTable *st) {
    char *var_name = vm_get_next_tok(cursor);
    char *value = vm_get_next_tok(cursor);
        
    Var *var = malloc(sizeof(Var));
    var->scope_level = 1;
    
    if (value[0] == '"' || (strlen(value) > 0 && !isdigit(value[0]))) {
        var->type = VAR_STRING;
        var->as.string = strdup(value);
    } else {
        var->type = VAR_NUMBER;
        var->as.number = atoi(value);
    }
    
    set_var(st, var_name, var);
}
