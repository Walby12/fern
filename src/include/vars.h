#ifndef VARS_H
#define VARS_H

typedef struct SymbolTable SymbolTable;

typedef enum VarType {
  VAR_STRING,
} VarType;

typedef struct Var {
  VarType type;
  int scope_level;
  union {
    char *string;
  } as;
} Var;

SymbolTable *sym_table_create();
void set_var(SymbolTable *st, const char *name, Var *data);
Var *get_var(SymbolTable *st, const char *name);
void destroy_sym_table(SymbolTable *st);

#endif
