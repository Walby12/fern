#include "parser.h"
#include "comp.h"
#include "lexer.h"

void parse(Compiler *comp) {
  lexe(comp);
  while (comp->cur_tok != END_OF_FILE) {
    if (comp->cur_tok == IDENT) {
      printf("IDENT: %s\n", comp->cur_word);
    }
    lexe(comp);
  }
  printf("Reached end of file\n");
}
