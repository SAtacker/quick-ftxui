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

enum block_alignment { VERTICAL, HORIZONTAL };

typedef boost::variant<nil, boost::recursive_wrapper<button>,
                       boost::recursive_wrapper<input>,
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

struct expression {
    block_alignment al;
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

BOOST_FUSION_ADAPT_STRUCT(client::quick_ftxui_ast::expression,
                          (std::list<client::quick_ftxui_ast::node>, expr)
                          (client::quick_ftxui_ast::block_alignment, al)
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
        switch (expr.al) {
        case quick_ftxui_ast::block_alignment::VERTICAL: {
            data->components.push_back(ftxui::Container::Vertical({}));
            break;
        }
        case quick_ftxui_ast::block_alignment::HORIZONTAL: {
            data->components.push_back(ftxui::Container::Horizontal({}));
            break;
        }
        default:
            throw std::runtime_error("Should never reach here");
            break;
        }
        ast_printer(data, indent + tabsize)(expr);
    }

    void operator()(quick_ftxui_ast::button const &text) const {
        tab(indent + tabsize);
        std::cout << "button: " << text << std::endl;
        if (text.func == "Exit") {
            if (data->components.size() > 0) {
                auto last = data->components.back().get();
                assert(last != nullptr);
                last->Add(ftxui::Button(text.placeholder,
                                        data->screen->ExitLoopClosure()));
            } else {
                data->components.push_back(ftxui::Container::Vertical({
                    ftxui::Button(text.placeholder,
                                  data->screen->ExitLoopClosure()),
                }));
            }
        }
    }

    void operator()(quick_ftxui_ast::input const &text) const {
        tab(indent + tabsize);
        std::cout << "input: " << text << std::endl;
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
              << "Node | Alignment:" << expr.al << std::endl;
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

        node = button_comp | input_comp | expression;

        expression = '{' >> *node >> '}' > alignment_kw;

        // Debugging and error handling and reporting support.
        BOOST_SPIRIT_DEBUG_NODES(
            (button_comp)(expression)(node)(input_comp)(button_comp));

        // Error handling
        on_error<fail>(button_comp, error_handler(_4, _3, _2));
    }
    qi::rule<Iterator, quick_ftxui_ast::expression(), ascii::space_type>
        expression;
    qi::rule<Iterator, quick_ftxui_ast::node(), ascii::space_type> node;
    qi::rule<Iterator, quick_ftxui_ast::button(), ascii::space_type>
        button_comp;
    qi::rule<Iterator, quick_ftxui_ast::input(), ascii::space_type> input_comp;
    qi::rule<Iterator, std::string(), ascii::space_type> quoted_string;
    qi::symbols<char, quick_ftxui_ast::block_alignment> alignment_kw;
};
} // namespace quick_ftxui_parser

} // namespace client

#endif // QUICK_FTXUI_HPP
