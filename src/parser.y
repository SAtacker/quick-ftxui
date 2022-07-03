%{
#include <stdlib.h>
#include <stdio.h>

extern void yyerror(const char* s);
extern int yylex();
extern int yyparse();
extern FILE* yyin;

extern int linenumber;
#define YYDEBUG 1
%}

%define parse.error verbose
%glr-parser 

%union{
    struct symbol* symbol_handle;
    struct ast_node *node;
    struct ast_node_statements *statements;
    struct ast_node_compound_statement *compound_statement;
    struct ast_node_button_component *button_component;
}

%token button toggle
%token red green blue
%token LBRACE RBRACE
%token COMMA SEMICOLON

%type <node> translation_unit program
%type <statements> statement 
%type <compound_statement> statement_list compound_statement 
%type <button_component> button_component
%start start

%%
start: translation_unit {
        ast = $1;
     }
     ;

translation_unit: program {
                    $$ = create_translation_unit();
                    $$ = add_program_unit($$, $1);
                }
	            | translation_unit program {
                    $$ = add_program_unit($1, $2);
                }
	            ;

program: statement {
        $$ = (ast_node*)$1;     
       }
       ;

compound_statement: LBRACE statement_list RBRACE {
                    $$ = $2;
                  }
                  ;

statement_list: statement {
                $$ = create_compound_statement_node();
                $$ = add_compound_statement_node($$, $1);
              }
              | statement_list statement {
                $$  = add_compound_statement_node($1, $2);
              }
              ;

statement: compound_statement {
            $$ = create_statement_node(AST_NODE_COMPOUND_STATEMENT, (void*)$1);
         }
         | button_component {
            $$ = create_statement_node(AST_NODE_BUTTON, (void*)$1); 
         }
         ;

button_component: button COMMA red SEMICOLON {
                    $$ = create_button_component_node($1, $3);

                }     
                | button COMMA blue SEMICOLON {
                    $$ = create_button_component_node($1, $3);

                }
                | button COMMA green SEMICOLON {
                    $$ = create_button_component_node($1, $3);

                }
                ; 
%%
void yyerror (const char *s) 
{
    fprintf (stderr, "%d : error: %s\n", linenumber, s);
    exit(0);
}
}