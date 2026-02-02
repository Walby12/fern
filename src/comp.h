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
  END_OF_FILE,
} Token;

typedef struct Compiler {
  Token cur_tok;
  char *src;
  const char *cur_word;
  size_t index;
  size_t line;
} Compiler;

Compiler *set_up_comp();
void comp_end(Compiler *comp);
const char *tok_to_string(Compiler *comp, Token t);

#endif
