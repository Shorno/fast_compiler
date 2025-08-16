%{
#include <stdio.h>
#include "ast.h"          /* ASTNode for %union */
extern int yylex(void);   /* silence "implicit declaration" */
void yyerror(const char *s);  /* declare yyerror function */

ASTNode *root = NULL;     /* global AST root */
%}

/* ---------- semantic values ---------- */
%union {
    int      ival;
    char    *sval;
    ASTNode *node;
}

/* ---------- tokens ---------- */
%token <ival> NUMBER
%token <sval> IDENTIFIER
%token ASSIGN PLUS MINUS MULTIPLY DIVIDE
%token LPAREN RPAREN SEMICOLON NEWLINE

/* ---------- non-terminal types ---------- */
%type <node> line statement expression term factor

/* ---------- precedence ---------- */
%left PLUS MINUS
%left MULTIPLY DIVIDE

%start line
%%


line
      : statement NEWLINE            { root = $1; }
      | statement SEMICOLON          { root = $1; }
      | statement                    { root = $1; }  /* Allow statement without terminator */
      ;

statement
      : IDENTIFIER ASSIGN expression { $$ = create_assignment_node($1, $3); }
      | expression                   { $$ = $1; }
      ;

expression
      : expression PLUS  term        { $$ = create_binop_node(OP_PLUS,  $1, $3); }
      | expression MINUS term        { $$ = create_binop_node(OP_MINUS, $1, $3); }
      | term                         { $$ = $1; }
      ;

term
      : term MULTIPLY factor         { $$ = create_binop_node(OP_MULTIPLY, $1, $3); }
      | term DIVIDE   factor         { $$ = create_binop_node(OP_DIVIDE,   $1, $3); }
      | factor                       { $$ = $1; }
      ;

factor
      : NUMBER                       { $$ = create_number_node($1); }
      | IDENTIFIER                   { $$ = create_variable_node($1); }
      | LPAREN expression RPAREN     { $$ = $2; }
      ;
%%


void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
}
