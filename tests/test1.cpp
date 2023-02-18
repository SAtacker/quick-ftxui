#include "quick-ftxui.hpp"
#include <catch2/catch_test_macros.hpp>
#include <string>

auto parse_helper(std::string &&str) {
    typedef std::string::const_iterator iterator_type;
    typedef client::quick_ftxui_parser::parser<iterator_type> parser;
    typedef client::quick_ftxui_ast::expression expression_type;

    parser parse;               // Our grammar
    expression_type expression; // Our program (AST)
    std::string::const_iterator iter = str.begin();
    std::string::const_iterator end = str.end();
    boost::spirit::ascii::space_type space;

    return boost::spirit::qi::phrase_parse(iter, end, parse, space,
                                           expression) &&
           iter == end;
}

TEST_CASE("Parse Simple") {
    //expect pass
    REQUIRE(parse_helper("Vertical{Button{\"amool\",\"bmpp\"}}"));
    REQUIRE(parse_helper("Horizontal{Button{\"amool\",\"bmpp\"}}"));
    REQUIRE(parse_helper("Horizontal{           Button{          \"amool\"    ,       "
                         "\"bmpp\" }           }"));
    REQUIRE(parse_helper("Vertical{           Button{          \"amool\"    ,       "
                         "\"bmpp\" }           }"));

    //expect fail
    REQUIRE(!parse_helper("\"amool\"{Button{\"amool\",\"bmpp\"}}"));
    REQUIRE(!parse_helper("\"amool\"{_Button{\"amool\",\"bmpp\"}}"));
    REQUIRE(!parse_helper("Vertical{_Button{\"amool\",\"bmpp\"}_}"));
    REQUIRE(!parse_helper("Horizontal_{_Button{\"amool\",\"bmpp\"}_}"));
    REQUIRE(!parse_helper("\"amool\"{Button{\"amool,\"bmpp\"}}"));
    REQUIRE(!parse_helper("Vertical{Button{\"amool\" . \"bmpp\"}}"));
}

TEST_CASE("Parse Complex") {
    REQUIRE(parse_helper("Vertical{\
                            Button{\"amool\",\"bmpp\"}      \
                            Button{\"amool\",\"bmpp\"}      \
                            Horizontal{\
                                Button{\"amool\",\"bmpp\"}      \
                                Button{\"amool\",\"bmpp\"}}     \
                            }"));
    REQUIRE(parse_helper("Vertical{\
        Button{\"amool\",\"bmpp\"}\
        }"));

    REQUIRE(parse_helper("Horizontal{\
        Button{\"amool\",\"bmpp\"}\
        }"));
}

TEST_CASE("Parse Multiple Components in any order") {
    REQUIRE(parse_helper("Horizontal{\
        Input{\"amool\" , \"bmpp\", \"cmqq\"}  \
        Button{\"amool\" , \"bmpp\"}  \
        }"));

    REQUIRE(parse_helper("Vertical{\
        Input{\"amool\" , \"bmpp\", \"cmqq\"}  \
        Button{\"amool\" , \"bmpp\"}  \
        }"));
}

TEST_CASE("Parse Recursive") {
    // expect pass
    REQUIRE(parse_helper("Vertical{\
        Button{\"amool\",\"bmpp\"}  \
        Button{\"amool\",\"bmpp\"}  \
        Horizontal{\
            Button{\"amool\",\"bmpp\"}  \
            Button{\"amool\",\"bmpp\"}  \
            Vertical{\
                Button{\"amool\",\"bmpp\"}  \
                Button{\"amool\",\"bmpp\"}  \
            }  \
        }  \
    }"));

    // expect fail
    REQUIRE(!parse_helper("Vertical{\
        Button{\"amool\",\"bmpp\"               \
            Button{\"amool\",\"bmpp\"}          \
        }\
        }"));

    REQUIRE(!parse_helper("Horizontal{\
        Button{\"amool\",\"bmpp\"               \
            Button{\"amool\",\"bmpp\"}          \
        }\
        }"));
    
    REQUIRE(!parse_helper("Vertical{\
        Button{\"amool\",\"bmpp\"  }             \
            Button{\"amool\",\"bmpp\"}          \
            {                                   \
                           Button{\"amool\",\"bmpp\"  }                         \
            }                       \
        }\
        }"));

    REQUIRE(!parse_helper("Horizontal{\
        Button{\"amool\",\"bmpp\"  }             \
            Button{\"amool\",\"bmpp\"}          \
            {                                   \
                           Button{\"amool\",\"bmpp\"  }                         \
            }                       \
        }\
        }"));
}
