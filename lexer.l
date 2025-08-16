%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"          /* ASTNode definition - must come first */
#include "parser.tab.h"   /* yylval, tokens, YY_BUFFER_STATE */
%}
%option noyywrap

%%
[0-9]+                    { yylval.ival = atoi(yytext);   return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]*    { yylval.sval = strdup(yytext); return IDENTIFIER; }
"="                       { return ASSIGN; }
"+"                       { return PLUS; }
"-"                       { return MINUS; }
"*"                       { return MULTIPLY; }
"/"                       { return DIVIDE; }
"("                       { return LPAREN; }
")"                       { return RPAREN; }
";"                       { return SEMICOLON; }
"\n"                      { return NEWLINE; }
[ \t\r]+                  { /* skip blanks */ }
.                         { printf("Unknown char %s\n", yytext); }
%%
