#include "lexer.h"
#include "comp.h"

#include <string.h>
#include <ctype.h>

void lexe(Compiler *comp) {
    while (comp->index < strlen(comp->src) && isspace((unsigned char)comp->src[comp->index])) {
        if (comp->src[comp->index] == '\n') {
            comp->line++;
        } 
        comp->index++;
    }

    if (comp->src[comp->index] == '\0') {
        comp->cur_tok = END_OF_FILE;
        return;
    }

    switch (comp->src[comp->index]) {
        case '+':
            comp->cur_tok = PLUS;
            comp->index++;
            break;
        case '(':
            comp->cur_tok = OPEN_PAREN;
            comp->index++;
            break;
        case ')':
            comp->cur_tok = CLOSE_PAREN;
            comp->index++;
            break;
        case ';':
            comp->cur_tok = SEMICOLON;
            comp->index++;
            break;
        case '"':
            char buff[1024];
            size_t i = 0;
            comp->index++;

            while (comp->index < strlen(comp->src) && comp->src[comp->index] != '"') {
                buff[i++] = comp->src[comp->index++];
            }
            buff[i] = '\0';

            comp->vals.word = strdup(buff);
            comp->cur_tok = STRING;
            comp->index++;
            break;
        case '=':
            comp->cur_tok = EQUALS;
            comp->index++;
            break;
        default:
            if (isalpha((unsigned char) comp->src[comp->index])) {
                char buff[1024];
                size_t i = 0;

                while (comp->index < strlen(comp->src) && !isspace((unsigned char) comp->src[comp->index]) &&
                       comp->src[comp->index] != ';' && comp->src[comp->index] != '(' && comp->src[comp->index] != ')') {
                    buff[i++] = comp->src[comp->index++];
                }
                buff[i] = '\0';
                           
                comp->vals.word = strdup(buff);
                comp->cur_tok = IDENT;
            } else if (isdigit((unsigned char) comp->src[comp->index])) {
                char buff[1024];
                size_t i = 0;

                while (comp->index < strlen(comp->src) && !isspace((unsigned char) comp->src[comp->index]) &&
                       comp->src[comp->index] != ';' && comp->src[comp->index] != '(' && comp->src[comp->index] != ')') {
                    buff[i++] = comp->src[comp->index++];
                }
                buff[i] = '\0';
                           
                comp->vals.number = atoi(buff);
                comp->cur_tok = NUMBER;                
            } else {
                printf("ERROR at line %zu: Invalid char '%c'\n", comp->line, comp->src[comp->index]);
                exit(1);
            }
            break;
    }
}
