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
    REQUIRE(parse_helper("Vertical{Button{\"amool\",\"bmpp\",Ascii}}"));
    REQUIRE(parse_helper("Vertical{Button{\"amool\",\"bmpp\",Simple}}"));
    REQUIRE(parse_helper("Vertical{Button{\"amool\",\"bmpp\",Animated}}"));
    REQUIRE(parse_helper("Vertical{Button{\"amool\",\"bmpp\"}}"));
    REQUIRE(parse_helper("Vertical{Button{\"amool\",System(\"ls\")}}"));
    REQUIRE(parse_helper("Horizontal{Button{\"amool\",\"bmpp\",Ascii}}"));
    REQUIRE(parse_helper("Horizontal{Button{\"amool\",\"bmpp\",Simple}}"));
    REQUIRE(parse_helper("Horizontal{Button{\"amool\",\"bmpp\",Animated}}"));
    REQUIRE(parse_helper("Horizontal{Button{\"amool\",\"bmpp\"}}"));
    REQUIRE(parse_helper("Horizontal{Button{\"amool\",System(\"mkdir dir1\")}}"));

    REQUIRE(parse_helper("Vertical{Slider{\"amool\", 2, 5, 100, 1}}"));
    REQUIRE(parse_helper("Horizontal{Slider{\"amool\", 2, 5, 100, 1}}"));

    REQUIRE(parse_helper(
        "Horizontal{           Button{          \"amool\"    ,       "
        "\"bmpp\"    ,       Simple }           }"));
    REQUIRE(parse_helper(
        "Vertical{           Button{          \"amool\"    ,       "
        "\"bmpp\"    ,       Simple }           }"));

    REQUIRE(parse_helper("Vertical{Menu{[\"Physics\"  \"Maths\"  \"Chemistry\" "
                         " \"Biology\"], 0}}"));
    REQUIRE(parse_helper("Vertical{Menu{[\"Physics\"  \"Maths\"  \"Chemistry\" "
                         " \"Biology\"], 0, Horizontal}}"));
    REQUIRE(parse_helper("Vertical{Menu{[\"Physics\"  \"Maths\"  \"Chemistry\" "
                         " \"Biology\"], 0, Vertical}}"));   
    REQUIRE(parse_helper("Vertical{Menu{[\"Physics\"  \"Maths\"  \"Chemistry\" "
                         " \"Biology\"], 0, Horizontal_Animated}}")); 
    REQUIRE(parse_helper("Vertical{Menu{[\"Physics\"  \"Maths\"  \"Chemistry\" "
                         " \"Biology\"], 0, Vertical_Animated}}"));
    REQUIRE(parse_helper("Vertical{Menu{[\"Physics\"  \"Maths\"  \"Chemistry\" "
                         " \"Biology\"], 0, Toggle}}"));                 
    REQUIRE(parse_helper("Horizontal{Menu{[\"Physics\"  \"Maths\"  "
                         "\"Chemistry\"  \"Biology\"], 0}}"));
        REQUIRE(parse_helper("Horizontal{Menu{[\"Physics\"  \"Maths\"  \"Chemistry\" "
                         " \"Biology\"], 0, Horizontal}}"));
    REQUIRE(parse_helper("Horizontal{Menu{[\"Physics\"  \"Maths\"  \"Chemistry\" "
                         " \"Biology\"], 0, Vertical}}"));   
    REQUIRE(parse_helper("Horizontal{Menu{[\"Physics\"  \"Maths\"  \"Chemistry\" "
                         " \"Biology\"], 0, Horizontal_Animated}}")); 
    REQUIRE(parse_helper("Horizontal{Menu{[\"Physics\"  \"Maths\"  \"Chemistry\" "
                         " \"Biology\"], 0, Vertical_Animated}}"));
    REQUIRE(parse_helper("Horizontal{Menu{[\"Physics\"  \"Maths\"  \"Chemistry\" "
                         " \"Biology\"], 0, Toggle}}"));   
    REQUIRE(parse_helper("Vertical{Toggle{[\"Opt1\" \"Opt2\"], 1}}"));
    REQUIRE(parse_helper("Horizontal{Toggle{[\"Opt1\" \"Opt2\"], 1}}"));
    REQUIRE(parse_helper("Vertical{Toggle{[\"Opt1\" \"Opt2\"], 0}}"));
    REQUIRE(parse_helper("Horizontal{Toggle{[\"Opt1\" \"Opt2\"], 0}}"));

    //expect fail
    REQUIRE(!parse_helper("\"amool\"{Button{\"amool\",\"bmpp\",\"cmqq\"}}"));
    REQUIRE(!parse_helper("\"amool\"{Button{\"amool\",\"bmpp\",Ascii}}"));
    REQUIRE(!parse_helper("\"amool\"{_Button{\"amool\",\"bmpp\",Ascii}"));
    REQUIRE(!parse_helper("Vertical{_Button{\"amool\",\"bmpp\",Ascii}_}"));
    REQUIRE(!parse_helper("Horizontal{Button{\"amool\",system(\"ls\")}}"));
    REQUIRE(!parse_helper("Vertical{Slider{\"amool\",\"bmpp\",\"cmqq\",\"dmrr\",\"emss\"}}"));
    REQUIRE(!parse_helper("Horizontal_{_Button{\"amool\",\"bmpp\",Simple}_}"));
    REQUIRE(!parse_helper("\"amool\"{Button{\"amool,\"bmpp\",Simple}}"));
    REQUIRE(!parse_helper("Vertical{Button{\"amool\" . \"bmpp\" . Ascii}}"));
    REQUIRE(parse_helper("Vertical{Toggle{[\"Opt1\" \"Opt2\"], 3}}"));
    REQUIRE(parse_helper("Vertical{Toggle{[\"Opt1\" \"Opt2\"], 8}}"));
}

TEST_CASE("Parse Complex") {
    REQUIRE(parse_helper("Vertical{\
                            Button{\"amool\",\"bmpp\",Simple}      \
                            Button{\"amool\",\"bmpp\",Ascii}      \
                            Horizontal{\
                                Button{\"amool\",\"bmpp\",Animated}      \
                                Button{\"amool\",System(\"mkdir dir1\")}}     \
                            }"));
    REQUIRE(parse_helper("Vertical{\
                            Button{\"amool\",\"bmpp\",Ascii}      \
                            Button{\"amool\",System(\"ls\"),Animated}      \
                            Horizontal{\
                                Slider{\"amool\", 40, 1, 100, 10}      \
                                Slider{\"amool\", 10, 1, 200, 100}}     \
                            }"));
    REQUIRE(parse_helper("Vertical{\
        Button{\"amool\",\"bmpp\",Ascii}\
        }"));

    REQUIRE(parse_helper("Horizontal{\
        Button{\"amool\",\"bmpp\",Ascii}\
        }"));
}

TEST_CASE("Parse Multiple Components in any order") {
    REQUIRE(parse_helper("Horizontal{\
        Slider{\"amool\" , 20 , 1 , 100 , 1}  \
        Button{\"amool\" , \"bmpp\", Animated}  \
        }"));

    REQUIRE(parse_helper("Vertical{\
        Slider{\"amool\" , 20, 1, 100, 1}  \
        Button{\"amool\" , \"bmpp\", Animated}  \
        }"));
    REQUIRE(parse_helper("Vertical{\
        Slider{\"amool\" , 20, 1, 100, 1}  \
        Button{\"amool\" , System(\"bmpp\"), Ascii}  \
        Menu{[\"Physics\"  \"Maths\"  \"Chemistry\"  \"Biology\"], 0}  \
        }"));
}

TEST_CASE("Parse Recursive") {
    // expect pass
    REQUIRE(parse_helper("Vertical{\
        Button{\"amool\",\"bmpp\", Animated}  \
        Button{\"amool\",\"bmpp\", Simple}  \
        Button{\"amool\",System(\"mkdir dir1\")}  \
        Horizontal{\
            Slider{\"amool\", 40, 1, 100, 10}  \
            Slider{\"amool\", 10, 1, 200, 100}  \
            Menu{[\"Physics\"  \"Maths\"  \"Chemistry\"  \"Biology\"], 0}  \
            Vertical{\
                Button{\"amool\",\"bmpp\", Ascii}  \
                Button{\"amool\",System(\"ls\"), Animated}  \
            }  \
        }  \
    }"));

    // expect fail
    REQUIRE(!parse_helper("Vertical{\
        Button{\"amool\",\"bmpp\",Ascii               \
            Button{\"amool\",\"bmpp\",\"cmqq\"}          \
        }\
        }"));

    REQUIRE(!parse_helper("Horizontal{\
        Button{\"amool\",\"bmpp\" Animated             \
            Button{\"amool\",\"bmpp\" Ascii}          \
        }\
        }"));

    REQUIRE(!parse_helper("Vertical{\
        Button{\"amool\",\"bmpp\",Ascii}             \
            Button{\"amool\", System(\"mkdir dir1\")}          \
            {                                   \
                           Button{\"amool\",\"bmpp\",Animated  }                         \
            }                       \
        }\
        }"));

    REQUIRE(!parse_helper("Horizontal{\
        Button{\"amool\",\"bmpp\",Ascii  }             \
            Button{\"amool\",\"bmpp\",Animated}          \
            {                                   \
                           Button{\"amool\",\"bmpp\",Simple  }                         \
            }                       \
        }\
        }"));
}
