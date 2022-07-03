#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <argp.h>
#include "codeprinter.h"
#include "ast.h"

#define VAL(str) #str
#define TOSTRING(str) VAL(str)

void yyerror(const char* s);
extern int yylex();
extern int yyparse();
extern FILE* yyin;

extern int linenumber;
extern ast_node *ast;

int main(int argc, char** argv)
{
{
 while(yyparse());
 int is_rpmsg_used = code_printer(ast);
}

void yyerror (const char *s) 
{
    fprintf (stderr, "%d : error: %s\n", linenumber, s);
    exit(0);
}
}