#include "ir_builder.h"
#include "comp.h"

#include <stdio.h>

void ir_print_stmt(Compiler *comp) {
    fprintf(comp->ir_file, "func_call print \"%s\"\n", comp->cur_word);
}

void ir_let_stmt(Compiler *comp, char *var_name) {
    fprintf(comp->ir_file, "bind %s \"%s\"\n", var_name, comp->cur_word);
}
