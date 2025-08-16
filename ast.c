#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

/* ───── tiny symbol table ───── */
typedef struct { char *name; int value; } Binding;
static Binding vars[128];
static int var_count = 0;

static int *lookup(const char *name)
{
    for (int i = 0; i < var_count; ++i)
        if (strcmp(vars[i].name, name) == 0) return &vars[i].value;

    vars[var_count].name  = strdup(name);
    vars[var_count].value = 0;
    return &vars[var_count++].value;
}

/* ───── constructors ───── */
ASTNode *create_number_node(int v)
{
    ASTNode *n = malloc(sizeof *n);
    n->type = NODE_NUMBER;
    n->data.number = v;
    return n;
}

ASTNode *create_binop_node(OperatorType op, ASTNode *l, ASTNode *r)
{
    ASTNode *n = malloc(sizeof *n);
    n->type = NODE_BINOP;
    n->data.binop.op    = op;
    n->data.binop.left  = l;
    n->data.binop.right = r;
    return n;
}

ASTNode *create_variable_node(char *name)
{
    ASTNode *n = malloc(sizeof *n);
    n->type = NODE_VARIABLE;
    n->data.variable.name = strdup(name);
    return n;
}

ASTNode *create_assignment_node(char *name, ASTNode *value)
{
    ASTNode *n = malloc(sizeof *n);
    n->type = NODE_ASSIGNMENT;
    n->data.assign.name  = strdup(name);
    n->data.assign.value = value;
    return n;
}

/* ───── evaluation ───── */
int evaluate_ast(ASTNode *n)
{
    switch (n->type) {
        case NODE_NUMBER:   return n->data.number;

        case NODE_VARIABLE: return *lookup(n->data.variable.name);

        case NODE_ASSIGNMENT: {
            int v = evaluate_ast(n->data.assign.value);
            *lookup(n->data.assign.name) = v;
            return v;
        }

        case NODE_BINOP: {
            int l = evaluate_ast(n->data.binop.left);
            int r = evaluate_ast(n->data.binop.right);
            switch (n->data.binop.op) {
                case OP_PLUS:      return l + r;
                case OP_MINUS:     return l - r;
                case OP_MULTIPLY:  return l * r;
                case OP_DIVIDE:    return l / r;
            }
        }
    }
    return 0; /* should not get here */
}

/* ───── pretty-print ───── */
static void indent(int n){ while(n--) putchar(' '); }

void print_ast(ASTNode *n, int ind)
{
    if (!n) return;
    indent(ind);
    switch (n->type) {
        case NODE_NUMBER:
            printf("NUMBER %d\n", n->data.number); break;

        case NODE_VARIABLE:
            printf("VAR %s\n", n->data.variable.name); break;

        case NODE_ASSIGNMENT:
            printf("ASSIGN %s\n", n->data.assign.name);
            print_ast(n->data.assign.value, ind+2); break;

        case NODE_BINOP:
            printf("BINOP %c\n", "+-*/"[n->data.binop.op]);
            print_ast(n->data.binop.left,  ind+2);
            print_ast(n->data.binop.right, ind+2); break;
    }
}

/* ───── cleanup ───── */
void free_ast(ASTNode *n)
{
    if (!n) return;
    switch (n->type) {
        case NODE_BINOP:
            free_ast(n->data.binop.left);
            free_ast(n->data.binop.right);
            break;
        case NODE_VARIABLE:
            free(n->data.variable.name);
            break;
        case NODE_ASSIGNMENT:
            free(n->data.assign.name);
            free_ast(n->data.assign.value);
            break;
        default: break;
    }
    free(n);
}
