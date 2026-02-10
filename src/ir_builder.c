#include "ir_builder.h"
#include "comp.h"
#include "vars.h"

#include <stdio.h>
#include <string.h>

void ir_print_stmt(Compiler *comp, char *value, int is_literal, VarType type) {
    char buff[2056];
    if (is_literal == 1) {
        if (type == VAR_STRING) {
            snprintf(buff, sizeof(buff), "func_call print \"%s\"\n", value);
        } else if (type == VAR_NUMBER) {
            snprintf(buff, sizeof(buff), "func_call print_num \"%s\"\n", value);
        }
    } else if (is_literal == 2) {
        snprintf(buff, sizeof(buff), "func_call print_int_as_str %s\n", value);
    } else {
        if (type == VAR_STRING) {
            snprintf(buff, sizeof(buff), "func_call print_str %s\n", value);
        } else if (type == VAR_NUMBER) {
            snprintf(buff, sizeof(buff), "func_call print_int %s\n", value);
        }
    }
    ir_append(comp, buff);
}

void ir_append(Compiler *comp, const char *str) {
    fprintf(comp->ir_file, "%s", str);
}

void ir_let_stmt(Compiler *comp, char *var_name, Var *var) {
    if (var->type == VAR_STRING) {
        fprintf(comp->ir_file, "bind %s \"%s\"\n", var_name, comp->vals.word);
    } else if (var->type == VAR_NUMBER) {
        fprintf(comp->ir_file, "bind %s %d\n", var_name, comp->vals.number);
    }
}

