#include "comp.h"

#include <stdlib.h>
#include <stdio.h>

Compiler *set_up_comp() {
    Compiler *comp = malloc(sizeof(Compiler));
    FILE *f = fopen("test.fern", "rb");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    comp->src = malloc(fsize + 1);
    fread(comp->src, fsize, 1, f);
    comp->src[fsize] = '\0';
    
    fclose(f);
    comp->index = 0;
    comp->line = 1;
    return comp;
}

void comp_end(Compiler *comp) {
    free(comp->src);
    free(comp);
}

const char *tok_to_string(Compiler *comp, Token t) {
  switch (t) {
    case IDENT:
      return comp->cur_word;
    case OPEN_PAREN:
      return "(";
    case CLOSE_PAREN:
      return ")";
    case SEMICOLON:
      return ";";
    case END_OF_FILE:
      return "end of file";
    default:
      return "TODO";
  }
}
