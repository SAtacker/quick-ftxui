#include "quick-ftxui.hpp"
#define BOOST_SPIRIT_QI_DEBUG

#include <boost/spirit/include/qi.hpp>
#include <fstream>
#include <iostream>

int main(int argc, char **argv) {
    typedef std::string::const_iterator iterator_type;
    typedef client::quick_ftxui_parser::parser<iterator_type> parser;
    typedef client::quick_ftxui_ast::expression expression_type;

    char const *filename;
    if (argc > 1) {
        filename = argv[1];
    } else {
        std::cerr << "Error: No input file provided." << std::endl;
        return 1;
    }

    std::ifstream in(filename, std::ios_base::in);

    if (!in) {
        std::cerr << "Error: Could not open input file: " << filename
                  << std::endl;
        return 1;
    }

    std::string source_code;     // We will read the contents here.
    in.unsetf(std::ios::skipws); // No white space skipping!
    std::copy(std::istream_iterator<char>(in), std::istream_iterator<char>(),
              std::back_inserter(source_code));

    parser parse;               // Our grammar
    expression_type expression; // Our program (AST)
    std::string::const_iterator iter = source_code.begin();
    std::string::const_iterator end = source_code.end();
    boost::spirit::ascii::space_type space;

    if (boost::spirit::qi::phrase_parse(iter, end, parse, space, expression) &&
        iter == end) {
        std::cout << "-------------------------\n";
        std::cout << "Parsing succeeded\n";
        std::cout << source_code << " Parses OK: " << std::endl;
        auto screen = ftxui::ScreenInteractive::Fullscreen();
        client::quick_ftxui_parser::component_meta_data data{&screen, {}};
        client::quick_ftxui_parser::ast_printer printer(&data, 0);
        printer(expression);
        if (data.components.size()) {
            auto component =
                ftxui::Container::Vertical(std::move(data.components));
            auto main_renderer = ftxui::Renderer(
                component, [&] { return ftxui::vbox({component->Render()}); });
            screen.Loop(main_renderer);
        }
    } else {
        std::cout << "-------------------------\n";
        std::cout << "Parsing failed\n";
        std::cout << "-------------------------\n";
    }
    return 0;
}