#include <stdio.h>
#include <string.h> // Added for strncmp
#include "ast.h"

// Forward declarations for flex/bison
extern int yyparse(void);
extern int yylex(void);
extern void yyrestart(FILE*);

// Flex buffer management functions
typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_string(const char *);
extern void yy_delete_buffer(YY_BUFFER_STATE);

extern ASTNode *root;    /* declared in parser.y */

int main(void)
{
    char line[1024];

    puts("Phase-2  REPL  –  arithmetic + assignments");
    puts("Type an expression or  var = expression");
    puts("Type 'quit' or 'exit' to quit");
    puts("");

    while (1) {
        printf(">>> ");
        fflush(stdout);

        // Get input from user
        if (!fgets(line, sizeof(line), stdin)) {
            // If fgets fails for any reason, just exit
            printf("\nExiting...\n");
            break;
        }

        // Check for empty line or just whitespace
        if (line[0] == '\n' || line[0] == '\0') {
            continue;
        }

        // Check for quit commands (case insensitive)
        if (strncmp(line, "quit", 4) == 0 || strncmp(line, "exit", 4) == 0 ||
            strncmp(line, "QUIT", 4) == 0 || strncmp(line, "EXIT", 4) == 0) {
            printf("Goodbye!\n");
            break;
        }

        YY_BUFFER_STATE buf = yy_scan_string(line);
        if (yyparse() == 0) {
            if (root) {
                print_ast(root, 0);
                printf("Value = %d\n\n", evaluate_ast(root));
                free_ast(root);
                root = NULL;
            }
        } else {
            puts("Parsing failed! Try again or type 'quit' to exit.\n");
        }
        yy_delete_buffer(buf);
    }

    return 0;
}
