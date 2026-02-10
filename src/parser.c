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
      if (strcmp(comp->vals.word, "print") == 0) {
        
        parse_expect(comp, OPEN_PAREN);
        Token t = parse_get_next_tok(comp);
        if (t == IDENT) {
          Var *found = get_var(comp->st, comp->vals.word);

          if (!found) {
            printf("ERROR at line %zu: Unknow variable: %s\n", comp->line, comp->vals.word);
            exit(1);
          }

          if (found->type != VAR_STRING) {
            printf("ERROR at line %zu: Expected variable %s to be str but got: %s\n", comp->line, comp->vals.word, var_type_to_string(found->type));
            exit(1);
          }
          parse_expect(comp, CLOSE_PAREN);
          ir_print_stmt(comp, comp->vals.word, 0);
        } else if (t != STRING) {
          printf("ERROR at line %zu: Expected a string or a str variable but got: %s\n", comp->line, tok_to_string_case_1(comp, comp->cur_tok));
          exit(1);
        } else {
          parse_expect(comp, CLOSE_PAREN);
          ir_print_stmt(comp, comp->vals.word, 1); 
        }
      } else if (strcmp(comp->vals.word, "let") == 0) {
        parse_expect(comp, IDENT);
        char *var_name = strdup(comp->vals.word);

        parse_expect(comp, EQUALS);
        Token t = parse_get_next_tok(comp);
        VarType var_type = VAR_NULL;
        Var *var = malloc(sizeof(Var));        
        
        switch (t) {
          case STRING:
            var_type = VAR_STRING;
            var->as.string = strdup(comp->vals.word);
            break;
          case NUMBER:
            var_type = VAR_NUMBER;
            var->as.number = comp->vals.number;
            break;
          default:
            printf("TODO\n");
        }
        
        var->type = var_type;
        var->scope_level = 1;

        set_var(comp->st, var_name, var);
        ir_let_stmt(comp, var_name, var);
        } else {
        printf("ERROR at line %zu: Invalid stmt '%s'\n", comp->line, comp->vals.word);
        exit(1);
        }
      parse_expect(comp, SEMICOLON);
      break;
    default:
      printf("ERROR at line %zu: Invalid stmt %s\n", comp->line, tok_to_string_case_1(comp, comp->cur_tok));
      exit(1);
  }
}
