#include "ir_builder.h"
#include "comp.h"

#include <stdio.h>

void vm_print_stmt(Compiler *comp) {
    fprintf(comp->ir_file, "func_call print\n");
}
