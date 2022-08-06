#include "ast.h"
#include "codeprinter.h"
#include <argp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VAL(str) #str
#define TOSTRING(str) VAL(str)

extern int yylex();
extern int yyparse();
extern FILE *yyin;

extern int linenumber;
extern ast_node *ast;

void yyerror(const char *s) {
  fprintf(stderr, "%d : error: %s\n", linenumber, s);
  exit(0);
}

int main(int argc, char **argv) {
  while (yyparse())
    ;
  int is_rpmsg_used;
  if (ast != NULL) {
    is_rpmsg_used = code_printer(ast);
    ast_node_dump(ast);
  }
}
