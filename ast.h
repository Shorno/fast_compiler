#ifndef AST_H
#define AST_H

typedef enum {
    NODE_NUMBER,
    NODE_BINOP,
    NODE_VARIABLE,
    NODE_ASSIGNMENT
} NodeType;

typedef enum {
    OP_PLUS, OP_MINUS, OP_MULTIPLY, OP_DIVIDE
} OperatorType;

typedef struct ASTNode {
    NodeType type;
    union {
        int number;                       /* NUMBER                     */
        struct {                          /* BINOP                      */
            OperatorType op;
            struct ASTNode *left;
            struct ASTNode *right;
        } binop;
        struct { char *name; } variable;  /* VARIABLE                   */
        struct {                          /* ASSIGNMENT                 */
            char *name;
            struct ASTNode *value;
        } assign;
    } data;
} ASTNode;

/* constructors */
ASTNode *create_number_node(int value);
ASTNode *create_binop_node(OperatorType op,
                           ASTNode *left, ASTNode *right);
ASTNode *create_variable_node(char *name);
ASTNode *create_assignment_node(char *name, ASTNode *value);

/* evaluation helpers */
int  evaluate_ast(ASTNode *node);
void print_ast   (ASTNode *node, int indent);
void free_ast    (ASTNode *node);

#endif
