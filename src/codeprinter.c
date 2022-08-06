#include "codeprinter.h"

void ast_compound_statement_printer(ast_node_compound_statement *cmpd_stmt, FILE* handle, int is_func_def)
{
    int i = 0;
    ast_node_statements *temp;

    fprintf(handle, "%s", "{\n");
    vec_foreach(&cmpd_stmt->child_nodes, temp, i)
    {
        switch(temp->node_type)
        {
            case AST_NODE_COMPOUND_STATEMENT:
                ast_compound_statement_printer(((ast_node_statements*)temp)->child_nodes.compound_statement, handle, 0);
                break;

            case AST_NODE_BUTTON:
                ast_button_printer(((ast_node_statements*)temp)->child_nodes.button, handle);
                break;

        }
    }
    fprintf(handle, "%s", "}\n");
}

void ast_button_printer(ast_node_button_component *button, FILE* handle)
{
 if (button!= NULL && handle != NULL)
    {
        fprintf(handle, "\t  auto buttons = Container::Horizontal({Button(\"Hello\", [&] { value--; }, ButtonOption::Animated(Color::%s),", button->expression);

        fprintf(handle, "\t  auto component = Renderer(buttons, [&] {"
                        "return vbox({"
                        "vbox({"
                        "text(\"value = \" + std::to_string(value)),"
                        " separator(),"
                        "gauge(value * 0.01f),"
                        " }) | border,"
                        " buttons->Render(),"
                        "});"
                        "});");
    }
    
}

int code_printer(ast_node* ast)
{
    FILE* handle = fopen("/tmp/temp.cpp", "w+");

    if (handle == NULL)
    {
        fprintf(stderr, "Unable to create translated file\n");
        exit(0);
    }


    int i = 0;
    ast_node *temp;
    temp = NULL;

    fprintf(handle, "%s", BEGIN);
    fprintf(handle, "%s", MAIN);    

    vec_foreach(&ast->child_nodes, temp, i)
    {   
        switch(temp->node_type)
        {
            case AST_NODE_COMPOUND_STATEMENT:
                ast_compound_statement_printer(((ast_node_statements*)temp)->child_nodes.compound_statement, handle, 0);
                break;

            case AST_NODE_BUTTON:
                ast_button_printer(((ast_node_statements*)temp)->child_nodes.button, handle);
                break;
        }
    }
    fprintf(handle, "%s", END);
    fclose(handle);
    return 0;
}
