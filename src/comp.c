#include "comp.h"
#include "vars.h"

#include <stdlib.h>
#include <stdio.h>

int verbose = 0;

Compiler *set_up_comp(const char *in_file_name, const char *out_file_name) {
    Compiler *comp = malloc(sizeof(Compiler));
    comp->in_file_name = in_file_name;
    comp->ir_file = fopen(out_file_name, "w");
    if (comp->ir_file == NULL) {
      printf("ERROR: Failed to create: %s\n", out_file_name);
      exit(1);
    }
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

    comp->st = sym_table_create();
    return comp;
}

void comp_end(Compiler *comp) {
    fclose(comp->ir_file);
    free(comp->src);
    free(comp);
}

const char *tok_to_string_case_1(Compiler *comp, Token t) {
  static char buffer[256];
    
  switch (t) {
    case IDENT:
      snprintf(buffer, sizeof(buffer), "identifier %s", comp->vals.word);
      return buffer;
    case NUMBER:
      snprintf(buffer, sizeof(buffer), "number %d", comp->vals.number);
      return buffer;
    case OPEN_PAREN:
      return "'('";
    case CLOSE_PAREN:
      return "')'";
    case SEMICOLON:
      return "';'";
    case STRING:
      snprintf(buffer, sizeof(buffer), "string %s", comp->vals.word);
      return buffer;
    case END_OF_FILE:
      return "end of file";
    default:
      return "TODO";
  }
}

const char *tok_to_string_case_2(Token t) {
  switch (t) {
    case IDENT:
      return "an identifier";
    case NUMBER:
      return "a number";
    case OPEN_PAREN:
      return "'(''";
    case CLOSE_PAREN:
      return "')'";
    case SEMICOLON:
      return "';'";
    case STRING:
      return "a string";
    case END_OF_FILE:
      return "end of file";
    default:
      return "TODO";
  }
}
