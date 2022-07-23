#ifndef CODEPRINTER_H
#define CODEPRINTER_H

#include "ast.h"
#include "symbol_table.h"
#include "vec/vec.h"

#include <stdio.h>
#include <stdlib.h>

#define BEGIN                                                                  \
  "#include <memory> \n#include <string>\n#include "                           \
  "\"ftxui/component/captured_mouse.hpp\" \n#include "                         \
  "\"ftxui/component/component.hpp\"\n #include "                              \
  "\"ftxui/component/component_base.hpp\"\n #include "                         \
  "\"ftxui/component/screen_interactive.hpp\"\n#include "                      \
  "\"ftxui/dom/elements.hpp\"\n"
#define MAIN "  using namespace ftxui;\n int main(int argc, const char* argv[]) \n{\n"
#define END " \n\t auto screen = ScreenInteractive::FitComponent(); \n screen.Loop(component); \n return 0;\n}\n"


void ast_compound_statement_printer(ast_node_compound_statement *cmpd_stmt, FILE* handle, int is_func_def);
void ast_button_printer(ast_node_button_component *_button, FILE* handle);
int code_printer(ast_node* ast);

#endif
