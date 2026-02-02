#ifndef PARSER_H
#define PARSER_H

typedef struct Compiler Compiler;
typedef enum Token Token;

void parse(Compiler *comp);
void parse_expr(Compiler *comp);
void parse_expect(Compiler *comp, Token t);

#endif
