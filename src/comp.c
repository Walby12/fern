#include "comp.h"

#include <stdlib.h>
#include <stdio.h>

Compiler *set_up_comp(const char *in_file_name, const char *out_file_name) {
    Compiler *comp = malloc(sizeof(Compiler));
    comp->in_file_name = in_file_name;
    comp->ir_file = fopen(out_file_name, "w");
    if (comp->ir_file == NULL) {
      printf("ERROR: Failed to create: %s\n", out_file_name);
      exit(1);
    }
    fprintf(comp->ir_file, "");
    fclose(comp->ir_file);

    comp->ir_file = fopen(out_file_name, "a");
    if (comp->ir_file == NULL) {
      printf("ERROR: Failed to create file: %s\n", out_file_name);
      exit(1);
    }
    
    FILE *f = fopen(comp->in_file_name, "rb");
    if (f == NULL) {
      printf("ERROR: Could not open file: %s\n", comp->in_file_name);
      exit(1);
    } 

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
    fclose(comp->ir_file);
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
