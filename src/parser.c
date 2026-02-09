#include "parser.h"
#include "comp.h"
#include "lexer.h"
#include "ir_builder.h"
#include "vars.h"

#include <string.h>

Token parse_get_next_tok(Compiler *comp) {
  lexe(comp);
  return comp->cur_tok;
}

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
  
  if (verbose) printf("Finished producing ir\n\n");
}

void parse_expr(Compiler *comp) {
  switch (comp->cur_tok) {
    case IDENT:
      if (strcmp(comp->cur_word, "print") == 0) {
        
        parse_expect(comp, OPEN_PAREN);
        Token t = parse_get_next_tok(comp);
        if (t == IDENT) {
          Var *found = get_var(comp->st, comp->cur_word);

          if (!found) {
            printf("ERROR at line %zu: Unknow variable: %s\n", comp->line, comp->cur_word);
            exit(1);
          }
          parse_expect(comp, CLOSE_PAREN);
          ir_print_stmt(comp, comp->cur_word, 0);
        } else if (t != STRING) {
          printf("ERROR at line %zu: Expected a string or a str var but got: %s\n", comp->line, tok_to_string_case_1(comp, comp->cur_tok));
          exit(1);
        } else {
          parse_expect(comp, CLOSE_PAREN);
          ir_print_stmt(comp, comp->cur_word, 1); 
        }
      } else if (strcmp(comp->cur_word, "let") == 0) {
        parse_expect(comp, IDENT);
        char *var_name = strdup(comp->cur_word);

        parse_expect(comp, EQUALS);
        parse_expect(comp, STRING);

        Var *var = malloc(sizeof(Var));
        var->type = VAR_STRING;
        var->scope_level = 1;
        var->as.string = strdup(comp->cur_word);

        set_var(comp->st, var_name, var);
        ir_let_stmt(comp, var_name);
        } else {
        printf("ERROR at line %zu: Invalid stmt '%s'\n", comp->line, comp->cur_word);
        exit(1);
      }
      parse_expect(comp, SEMICOLON);
      break;
    default:
      printf("ERROR at line %zu: Invalid stmt %s\n", comp->line, tok_to_string_case_1(comp, comp->cur_tok));
      exit(1);
  }
}
