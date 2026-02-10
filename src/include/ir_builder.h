#ifndef IR_BUILDER_H
#define IR_BUILDER_H

typedef struct Compiler Compiler;
typedef struct Var Var;

void ir_print_stmt(Compiler *comp, const char *arg, int c);
void ir_let_stmt(Compiler *comp, char *var_name, Var *var);

#endif
