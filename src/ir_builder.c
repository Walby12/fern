#include "ir_builder.h"
#include "comp.h"

#include <stdio.h>

void ir_print_stmt(Compiler *comp, const char *arg, int c) {
    if (c != 0) fprintf(comp->ir_file, "func_call print \"%s\"\n", arg);
    else fprintf(comp->ir_file, "func_call print %s\n", arg);
}

void ir_let_stmt(Compiler *comp, char *var_name) {
    fprintf(comp->ir_file, "bind %s \"%s\"\n", var_name, comp->vals.word);
}
