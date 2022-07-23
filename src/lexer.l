%{
  #include <stdio.h>
  #include "parser.h"
  int linenumber = 1;

  void yyerror(char* s);
  int yylex();
%}

%option noyywrap
%x comment

whitespace           (\t|" "|\r)
parenthesis          ("{"|"}")
components           ("Button"|"Toggle")
colors               ("color:blue"|"color:red"|"color:green")
comma                ([,])
newline              (\n)
%%

{parenthesis}           {
  if (!strcmp(yytext, "{"))
  {
    return LBRACE;
  }
  else if (!strcmp(yytext, "}"))
  {
    return RBRACE;
  }
}

{components}           {
   if (!strcmp(yytext, "Button"))
  {
    return BUTTON ;
  }   
    if (!strcmp(yytext, "Toggle"))
  {
    return TOGGLE ;
  }  

}

{colors}                {
   if (!strcmp(yytext, "color:blue"))
  {
    return BLUE;
  } 
    if (!strcmp(yytext, "color:red"))
  {
    return RED;
  }
    if (!strcmp(yytext, "color:green"))
  {
    return GREEN;
  } 
}


{comma}                 {
  return COMMA;
}

<comment>\n     { linenumber++; }
<comment>.      ;
%%