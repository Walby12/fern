#ifndef IR_BUILDER_H
#define IR_BUILDER_H

typedef struct Compiler Compiler;
typedef struct Var Var;
typedef enum VarType VarType;

void ir_print_stmt(Compiler *comp, char *value, int is_literal, VarType type);
void ir_append(Compiler *comp, const char *str);
void ir_let_stmt(Compiler *comp, char *var_name, Var *var);

#endif
