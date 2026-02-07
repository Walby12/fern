#ifndef COMP_H
#define COMP_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum Token {
  IDENT,
  OPEN_PAREN,
  CLOSE_PAREN,
  SEMICOLON,
  STRING,
  END_OF_FILE,
} Token;

typedef struct Compiler {
  Token cur_tok;
  char *src;
  const char *cur_word;
  size_t index;
  size_t line;
  const char *in_file_name;
  FILE *ir_file;
} Compiler;

Compiler *set_up_comp(const char *in_file_name, const char *out_file_name);
void comp_end(Compiler *comp);
const char *tok_to_string_case_1(Compiler *comp, Token t);
const char *tok_to_string_case_2(Token t);

#endif
