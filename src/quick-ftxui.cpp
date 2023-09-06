#include "quick-ftxui.hpp"
#define BOOST_SPIRIT_QI_DEBUG

#include <boost/spirit/include/qi.hpp>
#include <fstream>
#include <iostream>

int main(int argc, char **argv) {
  typedef std::string::const_iterator iterator_type;
  typedef quick_ftxui::parser<iterator_type> parser;
  typedef quick_ftxui_ast::expression expression_type;

  char const *filename;
  if (argc > 1) {
    filename = argv[1];
  } else {
    std::cerr << "Error: No input file provided." << std::endl;
    return 1;
  }

  std::filesystem::path fp = filename;

  if (fp.extension() != ".qf") {
    std::cerr << "Error: File extension / type not recognised: " << filename
              << std::endl;
    return 1;
  }

  std::ifstream in(filename, std::ios_base::in);

  if (!in) {
    std::cerr << "Error: Could not open input file: " << filename << std::endl;
    return 1;
  }

  std::string source_code;     // We will read the contents here.
  in.unsetf(std::ios::skipws); // No white space skipping!
  std::copy(std::istream_iterator<char>(in), std::istream_iterator<char>(),
            std::back_inserter(source_code));

  quick_ftxui::parse_qf(source_code);

  for (auto It : quick_ftxui_ast::numbers) {
    std::cout << "int " << It.first << ": " << It.second << "\n";
  }
  for (auto It : quick_ftxui_ast::strings) {
    std::cout << "str " << It.first << ": " << It.second << "\n";
  }
  return 0;
}