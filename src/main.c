#include "lexer.h"
#include "comp.h"
#include "parser.h"

int main() {
  Compiler *comp = set_up_comp();
  parse(comp);
  comp_end(comp);
  return 0;
}
