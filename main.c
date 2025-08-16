#include <stdio.h>
#include "ast.h"

extern ASTNode *root;
extern int yyparse();
extern FILE *yyin;

int main() {
    printf("Simple Expression Compiler (Phase 1)\n");
    printf("Enter an expression (e.g., 2 + 3 * 4): ");
    fflush(stdout);

    yyin = stdin;

    if (yyparse() == 0) {
        printf("\nParsing successful!\n\n");
        printf("AST:\n");
        print_ast(root, 0);
        printf("\nResult: %d\n", evaluate_ast(root));
        free_ast(root);
    } else {
        printf("Parsing failed!\n");
    }

    return 0;
}
