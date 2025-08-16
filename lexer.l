%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "parser.tab.h"   /* YYSTYPE & tokens */
%}

%option noyywrap

%%
[0-9]+                  { yylval.ival = atoi(yytext);      return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.sval = strdup(yytext);    return IDENTIFIER; }
"+"                     { return PLUS; }
"-"                     { return MINUS; }
"*"                     { return MULTIPLY; }
"/"                     { return DIVIDE; }
"("                     { return LPAREN; }
")"                     { return RPAREN; }
";"                     { return SEMICOLON; }
"\n"                    { return NEWLINE; }
[ \t]+                  { /* ignore whitespace */ }
<<EOF>>                 { return 0; }  /* Return 0 on EOF to signal end */
.                       { printf("Unknown character: %s\n", yytext); }

%%
