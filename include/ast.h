#ifndef AST_H
#define AST_H

#include "vec/vec.h"
#include "symbol_table.h"
#include <stdio.h>

#define AST_NODE                     0
#define AST_NODE_TRANSLATIONAL_UNIT  1
#define AST_NODE_STATEMENTS          2
#define AST_NODE_COMPOUND_STATEMENT  3
#define AST_NODE_BUTTON              4

typedef vec_t(struct ast_node*) ast_nodes;
typedef vec_t(struct ast_node_statements*) ast_nodes_statements;

struct ast_node;
struct ast_node_statements;
struct ast_node_compound_statement;
struct ast_node_button_component;
struct ast_node_expression;

typedef struct ast_node ast_node;
typedef struct ast_node_statements ast_node_statements;
typedef struct ast_node_compound_statement ast_node_compound_statement;
typedef struct ast_node_button_component ast_node_button_component;
typedef struct ast_node_expression ast_node_expression;

struct ast_node 
{
    int node_type;
    ast_nodes child_nodes;
};

 struct ast_node_statements 
{
    int node_type;

    union child_nodes
    {
        ast_node_compound_statement *compound_statement;
        ast_node_button_component *button;
    }child_nodes;
};

 struct ast_node_compound_statement
{
    int node_type;
    
    ast_nodes_statements child_nodes;
};

 struct ast_node_button_component
{
    int node_type;

    char *expression;
};

ast_node *create_translation_unit();
ast_node *add_program_unit(ast_node *parent, ast_node *child);
ast_node_statements *create_statement_node(int node_type, void *child);
ast_node_compound_statement *create_compound_statement_node();
ast_node_compound_statement *add_compound_statement_node(ast_node_compound_statement *parent, void *child);
ast_node_button_component *create_button_component_node(char *exp);
void ast_node_dump(ast_node* ast);
void ast_node_type(int node_type);

#endif