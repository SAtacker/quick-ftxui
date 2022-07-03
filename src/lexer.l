%{
  #include <stdio.h>
  int linenumber = 1;

  void yyerror(char* s);
  int yylex();
%}

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

{components }           {
   if (!strcmp(yytext, "Button"))
  {
    return button ;
  }   
    if (!strcmp(yytext, "Toggle"))
  {
    return toggle ;
  }  

}

{colors}                {
   if (!strcmp(yytext, "color:blue"))
  {
    return blue;
  } 
    if (!strcmp(yytext, "color:red))
  {
    return red;
  }
    if (!strcmp(yytext, "color:green"))
  {
    return green;
  } 
}


{comma}                 {
  return COMMA;
}

<comment>\n     { linenumber++; }
<comment>.      ;
%%