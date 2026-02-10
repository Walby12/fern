#ifndef VARS_H
#define VARS_H

typedef struct SymbolTable SymbolTable;
typedef enum VarType {
  VAR_STRING,
  VAR_NUMBER,
  VAR_NULL,
} VarType;

typedef struct Var {
  VarType type;
  int scope_level;
  union {
    char *string;
    int number;
  } as;
} Var;

SymbolTable *sym_table_create();
void set_var(SymbolTable *st, const char *name, Var *data);
Var *get_var(SymbolTable *st, const char *name);
void destroy_sym_table(SymbolTable *st);
const char *var_type_to_string(VarType t);

#endif
