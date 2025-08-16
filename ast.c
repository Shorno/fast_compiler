#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

ASTNode *create_number_node(int value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_NUMBER;
    node->data.number = value;
    return node;
}

ASTNode *create_binop_node(OperatorType op, ASTNode *left, ASTNode *right) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_BINOP;
    node->data.binop.op = op;
    node->data.binop.left = left;
    node->data.binop.right = right;
    return node;
}

ASTNode *create_variable_node(char *name) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_VARIABLE;
    node->data.variable.name = strdup(name);
    return node;
}

ASTNode *create_assignment_node(char *name, ASTNode *value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = NODE_ASSIGNMENT;
    node->data.assignment.name = strdup(name);
    node->data.assignment.value = value;
    return node;
}

void print_ast(ASTNode *node, int indent) {
    if (!node) return;

    for (int i = 0; i < indent; i++) printf("  ");

    switch (node->type) {
        case NODE_NUMBER:
            printf("NUMBER: %d\n", node->data.number);
            break;
        case NODE_BINOP:
            printf("BINOP: ");
            switch (node->data.binop.op) {
                case OP_PLUS: printf("+\n"); break;
                case OP_MINUS: printf("-\n"); break;
                case OP_MULTIPLY: printf("*\n"); break;
                case OP_DIVIDE: printf("/\n"); break;
            }
            print_ast(node->data.binop.left, indent + 1);
            print_ast(node->data.binop.right, indent + 1);
            break;
        case NODE_VARIABLE:
            printf("VARIABLE: %s\n", node->data.variable.name);
            break;
        case NODE_ASSIGNMENT:
            printf("ASSIGNMENT: %s\n", node->data.assignment.name);
            print_ast(node->data.assignment.value, indent + 1);
            break;
        default:
            printf("Unknown node type\n");
    }
}

int evaluate_ast(ASTNode *node) {
    if (!node) return 0;

    switch (node->type) {
        case NODE_NUMBER:
            return node->data.number;
        case NODE_BINOP:
            switch (node->data.binop.op) {
                case OP_PLUS:
                    return evaluate_ast(node->data.binop.left) +
                           evaluate_ast(node->data.binop.right);
                case OP_MINUS:
                    return evaluate_ast(node->data.binop.left) -
                           evaluate_ast(node->data.binop.right);
                case OP_MULTIPLY:
                    return evaluate_ast(node->data.binop.left) *
                           evaluate_ast(node->data.binop.right);
                case OP_DIVIDE:
                    return evaluate_ast(node->data.binop.left) /
                           evaluate_ast(node->data.binop.right);
            }
            break;
        default:
            printf("Cannot evaluate node type\n");
            return 0;
    }
    return 0;
}

void free_ast(ASTNode *node) {
    if (!node) return;

    switch (node->type) {
        case NODE_BINOP:
            free_ast(node->data.binop.left);
            free_ast(node->data.binop.right);
            break;
        case NODE_VARIABLE:
            free(node->data.variable.name);
            break;
        case NODE_ASSIGNMENT:
            free(node->data.assignment.name);
            free_ast(node->data.assignment.value);
            break;
        default:
            break;
    }
    free(node);
}
