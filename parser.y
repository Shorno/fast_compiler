%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yylex();
void yyerror(const char *s);

ASTNode *root = NULL;
%}


/* semantic value container */

%union {
    int        ival;
    char      *sval;
    ASTNode   *node;
}

%token <ival> NUMBER
%token <sval> IDENTIFIER
%token PLUS MINUS MULTIPLY DIVIDE
%token LPAREN RPAREN SEMICOLON NEWLINE

%type <node> expression term factor program

%left PLUS MINUS
%left MULTIPLY DIVIDE

%start program

%%


program:
    expression NEWLINE      { root = $1; YYACCEPT; }
    | expression SEMICOLON  { root = $1; YYACCEPT; }
    | expression            { root = $1; YYACCEPT; }
    ;

expression:
    expression PLUS term    { $$ = create_binop_node(OP_PLUS, $1, $3); }
    | expression MINUS term { $$ = create_binop_node(OP_MINUS, $1, $3); }
    | term                  { $$ = $1; }
    ;

term:
    term MULTIPLY factor    { $$ = create_binop_node(OP_MULTIPLY, $1, $3); }
    | term DIVIDE factor    { $$ = create_binop_node(OP_DIVIDE, $1, $3); }
    | factor                { $$ = $1; }
    ;

factor:
    NUMBER                  { $$ = create_number_node($1); }
    | LPAREN expression RPAREN { $$ = $2; }
    ;

%%


void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
