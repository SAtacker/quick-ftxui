#ifndef QUICK_FTXUI_HPP
#define QUICK_FTXUI_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/phoenix/function.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/recursive_variant.hpp>

#include "ftxui/component/component.hpp"      // for Input, Renderer, Vertical
#include "ftxui/component/component_base.hpp" // for ComponentBase
#include "ftxui/component/component_options.hpp" // for InputOption
#include "ftxui/component/mouse.hpp"             // for ftxui
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp" // for text, hbox, separator, Element, operator|, vbox, border
#include "ftxui/screen/screen.hpp"
#include "ftxui/util/ref.hpp" // for Ref

#include <iostream>
#include <string>

namespace client {
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

namespace quick_ftxui_ast {
///////////////////////////////////////////////////////////////////////////
//  The AST
///////////////////////////////////////////////////////////////////////////
struct nil {};
struct button;
struct expression;
struct input;
struct slider;
struct menu;
struct toggle;
struct radio;

enum block_alignment { VERTICAL, HORIZONTAL };

typedef boost::variant<
    nil, boost::recursive_wrapper<button>, boost::recursive_wrapper<input>,
    boost::recursive_wrapper<slider>, boost::recursive_wrapper<menu>,
    boost::recursive_wrapper<toggle>, boost::recursive_wrapper<radio>,
    boost::recursive_wrapper<expression>>
    node;

struct button {
    std::string placeholder;
    std::string func;
};

struct input {
    std::string placeholder;
    std::string temp;
    std::string option;
};

struct slider {
    std::string label;
    int value;
    int min;
    int max;
    int increment;
};

struct menu {
    std::vector<std::string> entries;
    int selected = 0;
};

struct toggle {
    std::vector<std::string> entries;
    int selected;
};

struct radio {
    std::vector<std::string> entries;
    int selected = 0;
};

struct expression {
    block_alignment align;
    std::list<node> expr;
};

// print function for debugging
inline std::ostream &operator<<(std::ostream &out, nil) {
    out << "nil";
    return out;
}

// print function for debugging
inline std::ostream &operator<<(std::ostream &out, button b) {
    out << "Placeholder: " << b.placeholder << " | Func: " << b.func;
    return out;
}

// print function for debugging
inline std::ostream &operator<<(std::ostream &out, input b) {
    out << "Placeholder: " << b.placeholder << " | Temp: " << b.temp
        << " | Options: " << b.option;
    return out;
}

inline std::ostream &operator<<(std::ostream &out, slider b) {
    out << "Label: " << b.label << " | Value: " << b.value
        << " | Min: " << b.min << " | Max: " << b.max
        << " | Increment: " << b.increment;
    return out;
}

} // namespace quick_ftxui_ast
} // namespace client

// clang-format off
BOOST_FUSION_ADAPT_STRUCT(client::quick_ftxui_ast::button,
                          (std::string, placeholder)
                          (std::string, func)
)

BOOST_FUSION_ADAPT_STRUCT(client::quick_ftxui_ast::input,
                          (std::string, placeholder)
                          (std::string, temp)
                          (std::string, option)
)

BOOST_FUSION_ADAPT_STRUCT(client::quick_ftxui_ast::slider,
                          (std::string, label)
                          (int, value)
                          (int, min)
                          (int, max)
                          (int, increment)
)

BOOST_FUSION_ADAPT_STRUCT(client::quick_ftxui_ast::menu,
                          (std::vector<std::string>, entries)
                          (int, selected)
)

BOOST_FUSION_ADAPT_STRUCT(client::quick_ftxui_ast::toggle,
                          (std::vector <std::string> , entries)
                          (int, selected)
)

BOOST_FUSION_ADAPT_STRUCT(client::quick_ftxui_ast::radio,
                          (std::vector<std::string>, entries)
                          (int, selected)
)

BOOST_FUSION_ADAPT_STRUCT(client::quick_ftxui_ast::expression,
                          (client::quick_ftxui_ast::block_alignment, align)
                          (std::list<client::quick_ftxui_ast::node>, expr)
)

// clang-format on

namespace client {
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

namespace quick_ftxui_parser {
using boost::phoenix::function;

int const tabsize = 4;

void tab(int indent) {
    for (int i = 0; i < indent; ++i)
        std::cout << ' ';
}

struct component_meta_data {
    ftxui::ScreenInteractive *screen;
    ftxui::Components components;
};

struct ast_printer {
    ast_printer(component_meta_data *data_, int indent = 0)
        : indent(indent), data(data_) {}
    ast_printer(component_meta_data *data_) : data(data_) {}

    void operator()(quick_ftxui_ast::expression const &) const;

    int indent;

    component_meta_data *data;
};

struct node_printer : boost::static_visitor<> {
    node_printer(component_meta_data *data_, int indent = 0)
        : indent(indent), data(data_) {}

    void operator()(client::quick_ftxui_ast::expression const &expr) const {
        component_meta_data data_nest{data->screen};
        ast_printer(&data_nest, indent + tabsize)(expr);

        switch (expr.align) {
        case quick_ftxui_ast::block_alignment::VERTICAL: {
            data->components.push_back(
                ftxui::Container::Vertical({(data_nest).components}));
            break;
        }
        case quick_ftxui_ast::block_alignment::HORIZONTAL: {
            data->components.push_back(
                ftxui::Container::Horizontal({(data_nest).components}));
            break;
        }
        default:
            throw std::runtime_error("Should never reach here");
            break;
        }
    }

    void operator()(quick_ftxui_ast::button const &text) const {
        tab(indent + tabsize);
        std::cout << "button: " << text << std::endl;
        if (text.func == "Exit") {
            data->components.push_back(ftxui::Button(
                text.placeholder, data->screen->ExitLoopClosure()));
        }
    }

    void operator()(quick_ftxui_ast::slider const &text) const {
        tab(indent + tabsize);
        std::cout << "slider" << text << std::endl;
        data->components.push_back(ftxui::Slider(text.label,
                                                 (int *)(&text.value), text.min,
                                                 text.max, text.increment));
    }

    void operator()(quick_ftxui_ast::input const &text) const {
        tab(indent + tabsize);
        std::cout << "input: " << text << std::endl;
    }

    void operator()(quick_ftxui_ast::menu const &text) const {
        tab(indent + tabsize);
        data->components.push_back(
            ftxui::Menu(&text.entries, (int *)&text.selected));
    }

    void operator()(quick_ftxui_ast::toggle const &text) const {
        tab(indent + tabsize);
        data->components.push_back(
            ftxui::Toggle(&text.entries, (int *)&text.selected));
    }

    void operator()(quick_ftxui_ast::radio const &text) const {
        tab(indent + tabsize);
        data->components.push_back(
            ftxui::Radiobox(&text.entries, (int *)&text.selected));
    }

    void operator()(quick_ftxui_ast::nil const &text) const {
        tab(indent + tabsize);
        std::cout << "nil: \"" << text << '"' << std::endl;
    }

    int indent;
    component_meta_data *data;
};

void ast_printer::operator()(
    client::quick_ftxui_ast::expression const &expr) const {
    tab(indent);
    std::cout << "tag: "
              << "Node | Alignment: " << expr.align << std::endl;
    tab(indent);
    std::cout << '{' << std::endl;

    for (quick_ftxui_ast::node const &node : expr.expr) {
        boost::apply_visitor(node_printer(data, indent), node);
    }

    tab(indent);
    std::cout << '}' << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
//  The error handler
///////////////////////////////////////////////////////////////////////////////
struct error_handler_ {
    template <typename, typename, typename> struct result {
        typedef void type;
    };

    template <typename Iterator>
    void operator()(qi::info const &what, Iterator err_pos,
                    Iterator last) const {
        std::cout << "Error! Expecting " << what // what failed?
                  << " here: \""
                  << std::string(err_pos, last) // iterators to error-pos, end
                  << "\"" << std::endl;
    }
};

function<error_handler_> const error_handler = error_handler_();

template <typename Iterator>
struct parser
    : qi::grammar<Iterator, quick_ftxui_ast::expression(), ascii::space_type> {
    parser() : parser::base_type(expression) {
        qi::char_type char_;
        qi::uint_type uint_;
        qi::_2_type _2;
        qi::_3_type _3;
        qi::_4_type _4;

        using qi::fail;
        using qi::on_error;

        // clang-format off
        alignment_kw
          .add
          ("Vertical", quick_ftxui_ast::block_alignment::VERTICAL)
          ("Horizontal", quick_ftxui_ast::block_alignment::HORIZONTAL)
          ;
        // clang-format on

        quoted_string %= qi::lexeme['"' >> +(char_ - '"') >> '"'];

        button_comp %= qi::lit("Button") >> '{' >> quoted_string >> ',' >>
                       quoted_string >> '}';

        input_comp %= qi::lit("Input") >> '{' >> quoted_string >> ',' >>
                      quoted_string >> ',' >> quoted_string >> '}';

        slider_comp %= qi::lit("Slider") >> '{' >> quoted_string >> ',' >>
                       qi::int_ >> ',' >> qi::int_ >> ',' >> qi::int_ >> ',' >>
                       qi::int_ >> '}';

        menu_comp %= qi::lit("Menu") >> '{' >> '[' >> *quoted_string >> ']' >>
                     ',' >> qi::int_ >> '}';

        toggle_comp %= qi::lit("Toggle") >> '{' >> '[' >> *quoted_string >>
                       ']' >> ',' >> qi::int_ >> '}';

        radio_comp %= qi::lit("Radiobox") >> '{' >> '[' >> *quoted_string >>
                      ']' >> ',' >> qi::int_ >> '}';

        node = button_comp | input_comp | slider_comp | menu_comp |
               toggle_comp | radio_comp | expression;

        expression = alignment_kw >> '{' >> *node >> '}';

        // Debugging and error handling and reporting support.
        BOOST_SPIRIT_DEBUG_NODES((button_comp)(expression));

        // Error handling
        on_error<fail>(button_comp, error_handler(_4, _3, _2));
    }
    qi::rule<Iterator, quick_ftxui_ast::expression(), ascii::space_type>
        expression;
    qi::rule<Iterator, quick_ftxui_ast::node(), ascii::space_type> node;
    qi::rule<Iterator, quick_ftxui_ast::button(), ascii::space_type>
        button_comp;
    qi::rule<Iterator, quick_ftxui_ast::input(), ascii::space_type> input_comp;
    qi::rule<Iterator, quick_ftxui_ast::menu(), ascii::space_type> menu_comp;
    qi::rule<Iterator, quick_ftxui_ast::toggle(), ascii::space_type>
        toggle_comp;
    qi::rule<Iterator, quick_ftxui_ast::radio(), ascii::space_type> radio_comp;
    qi::rule<Iterator, std::string(), ascii::space_type> quoted_string;
    qi::rule<Iterator, quick_ftxui_ast::slider(), ascii::space_type>
        slider_comp;
    qi::symbols<char, quick_ftxui_ast::block_alignment> alignment_kw;
};
} // namespace quick_ftxui_parser

} // namespace client

#endif // QUICK_FTXUI_HPP
