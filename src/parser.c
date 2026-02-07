#include "parser.h"
#include "comp.h"
#include "lexer.h"
#include "ir_builder.h"

#include <string.h>

void parse_expect(Compiler *comp, Token t) {
  lexe(comp);
  if (comp->cur_tok != t) {
    printf("ERROR at line %zu: Expected %s but got %s\n", comp->line, tok_to_string_case_2(t), tok_to_string_case_1(comp, comp->cur_tok));
    exit(1);
  }
}

void parse(Compiler *comp) {
  lexe(comp);
  while (comp->cur_tok != END_OF_FILE) {
    parse_expr(comp);
    lexe(comp);
  }
  printf("Finished producing ir\n");
}

void parse_expr(Compiler *comp) {
  switch (comp->cur_tok) {
    case IDENT:
      if (strcmp(comp->cur_word, "print") == 0) {
        parse_expect(comp, OPEN_PAREN);
        parse_expect(comp, STRING);
        parse_expect(comp, CLOSE_PAREN);
        parse_expect(comp, SEMICOLON);
        ir_print_stmt(comp);
      } else {
        printf("ERROR at line %zu: Invalid stmt '%s'\n", comp->line, comp->cur_word);
        exit(1);
      }
      break;
    default:
      printf("ERROR at line %zu: Invalid stmt %s\n", comp->line, tok_to_string_case_1(comp, comp->cur_tok));
      exit(1);
  }
}
