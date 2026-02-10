#include "vars.h"
#include "khash.h"

#include <stdlib.h>
#include <string.h>

KHASH_MAP_INIT_STR(sym, Var*)

struct SymbolTable {
  khash_t(sym) *hash_table;
};

SymbolTable *sym_table_create() {
  SymbolTable *st = malloc(sizeof(SymbolTable));
  st->hash_table = kh_init(sym);
  return st;
}

void set_var(SymbolTable *st, const char *name, Var *data) {
  int ret;
  khiter_t k = kh_put(sym, st->hash_table, strdup(name), &ret);
  kh_value(st->hash_table, k) = data;
}

Var *get_var(SymbolTable *st, const char *name) {
  khiter_t k = kh_get(sym, st->hash_table, name);
  if (k == kh_end(st->hash_table)) {
    return NULL;
  }
  return kh_value(st->hash_table, k);
}

void destroy_sym_table(SymbolTable *st) {
  if (!st) return;

  khiter_t k;
  for (k = kh_begin(st->hash_table); k != kh_end(st->hash_table); ++k) {
    if (kh_exist(st->hash_table, k)) {
      free((char*)kh_key(st->hash_table, k));
    }
  }
  kh_destroy(sym, st->hash_table);
  free(st);
}

const char *var_type_to_string(VarType t) {
  switch (t) {
    case VAR_STRING:
      return "str";
    case VAR_NUMBER:
      return "int";
    default:
      return "TODO";
  }
}
