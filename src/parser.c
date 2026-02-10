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

Token peek_next_tok(Compiler *comp) {
    size_t saved_index = comp->index;
    Token saved_tok = comp->cur_tok;
    size_t saved_line = comp->line;
    
    char *saved_word = NULL;
    if (comp->vals.word != NULL) {
        saved_word = strdup(comp->vals.word);
    }
    int saved_number = comp->vals.number;
    
    lexe(comp);
    Token peeked = comp->cur_tok;
    
    comp->index = saved_index;
    comp->cur_tok = saved_tok;
    comp->line = saved_line;
    
    if (saved_word != NULL) {
        if (comp->vals.word != NULL) {
            free(comp->vals.word);
        }
        comp->vals.word = saved_word;
    }
    comp->vals.number = saved_number;
    
    return peeked;
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
        
        while (1) {
          Token t = parse_get_next_tok(comp);
          
          if (t == IDENT) {
            Var *found = get_var(comp->st, comp->vals.word);
            if (!found) {
              printf("ERROR at line %zu: Unknown variable: %s\n", comp->line, comp->vals.word);
              exit(1);
            }
            if (found->type == VAR_NUMBER) {
              ir_print_stmt(comp, comp->vals.word, 2, VAR_NUMBER);
            } else {
              ir_print_stmt(comp, comp->vals.word, 0, found->type);
            }
          } else if (t == STRING) {
            ir_print_stmt(comp, comp->vals.word, 1, VAR_STRING);
          } else if (t == NUMBER) {
            char num_str[64];
            snprintf(num_str, sizeof(num_str), "%d", comp->vals.number);
            ir_print_stmt(comp, num_str, 1, VAR_NUMBER);
          } else {
            printf("ERROR at line %zu: Expected string, number, or variable\n", comp->line);
            exit(1);
          }
          
          if (peek_next_tok(comp) == PLUS) {
            parse_get_next_tok(comp);
          } else {
            break;
          }
        }
        
        parse_expect(comp, CLOSE_PAREN);
        parse_expect(comp, SEMICOLON);
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
            printf("ERROR at line %zu: Unsupported variable type\n", comp->line);
            exit(1);
        }
        
        var->type = var_type;
        var->scope_level = 1;
        set_var(comp->st, var_name, var);
        ir_let_stmt(comp, var_name, var);
        parse_expect(comp, SEMICOLON);
      } else {
        printf("ERROR at line %zu: Invalid stmt '%s'\n", comp->line, comp->vals.word);
        exit(1);
      }
      break;
    default:
      printf("ERROR at line %zu: Invalid stmt %s\n", comp->line, tok_to_string_case_1(comp, comp->cur_tok));
      exit(1);
  }
}
