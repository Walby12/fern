#include "lexer.h"
#include "comp.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void lexe(Compiler *comp) {
  while (isspace(comp->src[comp->index])) {
    if (comp->src[comp->index] == '\n') {
      comp->line++;
    }
    comp->index++;
  }
  
  switch (comp->src[comp->index]) {
    default:
      char buff[1024];
      size_t i = 0;

      if (isalpha(comp->src[comp->index])) {
        while (comp->index < strlen(comp->src) && !isspace(comp->src[comp->index])) {
          buff[i++] = comp->src[comp->index++];
        }
        buff[i] = '\0';
        comp->cur_word = strdup(buff);
        comp->cur_tok = IDENT;
      } else {
        comp->cur_tok = END_OF_FILE;
      }
  } 
}
