#include "ast.h"

ast_node *create_translation_unit()
{
    ast_node *tu = (ast_node*)malloc(sizeof(ast_node));

    tu->node_type = AST_NODE_TRANSLATIONAL_UNIT;
    vec_init(&tu->child_nodes);

    return tu;
}

ast_node *add_program_unit(ast_node *parent, ast_node *child)
{
    vec_push(&parent->child_nodes, child);

    return parent;
}


ast_node_statements *create_statement_node(int node_type, void *child)
{
    ast_node_statements *stmt = (ast_node_statements*)malloc(sizeof(ast_node_statements));

    stmt->node_type = node_type;
    switch (node_type)
    {
        case AST_NODE_COMPOUND_STATEMENT:
            stmt->child_nodes.compound_statement = child;
            break;

        case AST_NODE_BUTTON:
            stmt->child_nodes.button = child;
            break;

    }
}

ast_node_compound_statement *create_compound_statement_node()
{
    ast_node_compound_statement *cmpd_stmt = (ast_node_compound_statement*)malloc(sizeof(ast_node_compound_statement));

    cmpd_stmt->node_type = AST_NODE_COMPOUND_STATEMENT;
    vec_init(&cmpd_stmt->child_nodes);

    return cmpd_stmt;
}

ast_node_compound_statement *add_compound_statement_node(ast_node_compound_statement *parent, ast_node_statements *child)
{
    vec_push(&parent->child_nodes, child);

    return parent;
}

ast_node_button_component *create_button_component_node(sym_ptr symbol, ast_node_expression *exp)
{
    ast_node_button_component *component_button = (ast_node_button_component*)malloc(sizeof(ast_node_button_component));

    component_button->node_type = AST_NODE_BUTTON;
    component_button->expression = exp;
    component_button->symbol_entry = symbol;

    return component_button;
}

void ast_node_dump(ast_node* ast)
{
    ast_node_type(ast->node_type);

    int i = 0;
    ast_node *temp;
    
    vec_foreach(&ast->child_nodes, temp, i)
    {
        ast_node_type(temp->node_type);   
    }
}

void ast_node_type(int node_type)
{
    switch (node_type)
    {
        case AST_NODE:
            printf("ast node");
            break;

        case AST_NODE_TRANSLATIONAL_UNIT:
            printf("ast translational unit");
            break;

        case AST_NODE_STATEMENTS:
            printf("ast statements");
            break;

        case AST_NODE_COMPOUND_STATEMENT:
            printf("ast compound statement");
            break;

        case AST_NODE_BUTTON:
            printf("ast button");
            break;
        
        default:
        break;
    }
printf("\n");
}
