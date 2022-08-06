%{
#include <stdlib.h>
#include <stdio.h>
#include "symbol_table.h"
#include "ast.h"
#include "codeprinter.h"

extern void yyerror(const char* s);
extern int yylex();
extern int yyparse();
extern ast_node *create_translation_unit();
extern FILE* yyin;
ast_node *ast = NULL;

extern int linenumber;
#define YYDEBUG 1
%}

%define parse.error verbose
%glr-parser 

%union{
    struct symbol* symbol_handle;
    char* color_type;
    struct ast_node *node;
    struct ast_node_statements *statements;
    struct ast_node_compound_statement *compound_statement;
    struct ast_node_button_component *button_component;
}

%left LBRACE RBRACE
%token COMMA SEMICOLON
%token <symbol_handle> BUTTON TOGGLE
%token <color_type> RED GREEN BLUE

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

statement:button_component {
            $$ = create_statement_node(AST_NODE_BUTTON, (void*)$1);
         } 
         | compound_statement {
            $$ = create_statement_node(AST_NODE_COMPOUND_STATEMENT, (void*)$1);
         }
         ;

button_component: BUTTON COMMA RED SEMICOLON {
                    $$ = create_button_component_node("color:red");
                }     
                | BUTTON COMMA BLUE SEMICOLON {
                    $$ = create_button_component_node("color:blue");

                }
                | BUTTON COMMA GREEN SEMICOLON {
                    $$ = create_button_component_node( "color:green");

                }
                ; 
%%
