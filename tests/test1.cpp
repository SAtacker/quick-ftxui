#include "quick-ftxui.hpp"
#include <catch2/catch_test_macros.hpp>
#include <string>

auto parse_helper(std::string &&str) {
  typedef std::string::const_iterator iterator_type;
  typedef quick_ftxui::parser<iterator_type> parser;
  typedef quick_ftxui_ast::expression expression_type;

  parser parse;               // Our grammar
  expression_type expression; // Our program (AST)
  std::string::const_iterator iter = str.begin();
  std::string::const_iterator end = str.end();
  boost::spirit::ascii::space_type space;

  return boost::spirit::qi::phrase_parse(iter, end, parse, space, expression) &&
         iter == end;
}

TEST_CASE("Parse Simple") {
  // expect pass
  REQUIRE(parse_helper("Vertical{Button{\"amool\",\"bmpp\",Ascii}}"));
  REQUIRE(parse_helper("Vertical{Button{\"amool\",\"bmpp\",Simple}}"));
  REQUIRE(parse_helper("Vertical{Button{\"amool\",\"bmpp\",Animated}}"));
  REQUIRE(parse_helper("Vertical{Button{\"amool\",\"bmpp\"}}"));
  REQUIRE(parse_helper("Vertical{str x Button{\"amool\",System(\"ls\"), x}}"));
  REQUIRE(parse_helper("Horizontal{Button{\"amool\",\"bmpp\",Ascii}}"));
  REQUIRE(parse_helper("Horizontal{Button{\"amool\",\"bmpp\",Simple}}"));
  REQUIRE(parse_helper("Horizontal{Button{\"amool\",\"bmpp\",Animated}}"));
  REQUIRE(parse_helper("Horizontal{Button{\"amool\",\"bmpp\"}}"));
  REQUIRE(parse_helper(
      "Horizontal{str y Button{\"amool\",System(\"mkdir dir1\"), y}}"));

  REQUIRE(parse_helper("Vertical{int x Slider{\"amool\", x, 5, 100, 1}}"));
  REQUIRE(parse_helper("Horizontal{int y Slider{\"amool\", y, 5, 100, 1}}"));

  REQUIRE(parse_helper(
      "Horizontal{           Button{          \"amool\"    ,       "
      "\"bmpp\"    ,       Simple }           }"));
  REQUIRE(
      parse_helper("Vertical{           Button{          \"amool\"    ,       "
                   "\"bmpp\"    ,       Simple }           }"));

  REQUIRE(parse_helper(
      "Vertical{int y Dropdown{[\"Physics\",  \"Maths\",  \"Chemistry\", "
      " \"Biology\",], y}}"));
  REQUIRE(parse_helper("Horizontal{int z Menu{[\"Physics\",  \"Maths\",  "
                       "\"Chemistry\",  \"Biology\",], z}}"));
  REQUIRE(parse_helper("Vertical{int opt Toggle{[\"Opt1\", \"Opt2\",], opt}}"));
  REQUIRE(parse_helper("Horizontal{int a Toggle{[\"Opt1\", \"Opt2\",], a}}"));
  REQUIRE(parse_helper("Vertical{int b Toggle{[\"Opt1\", \"Opt2\",], b}}"));
  REQUIRE(parse_helper("Horizontal{int x_ Toggle{[\"Opt1\", \"Opt2\",], x_}}"));

  // expect fail
  REQUIRE(!parse_helper("\"amool\"{Button{\"amool\",\"bmpp\",\"cmqq\"}}"));
  REQUIRE(!parse_helper("\"amool\"{Button{\"amool\",\"bmpp\",Ascii}}"));
  REQUIRE(!parse_helper("\"amool\"{_Button{\"amool\",\"bmpp\",Ascii}"));
  REQUIRE(!parse_helper("Vertical{_Button{\"amool\",\"bmpp\",Ascii}_}"));
  REQUIRE(!parse_helper("Horizontal{Button{\"amool\",system(\"ls\")}}"));
  REQUIRE(!parse_helper(
      "Vertical{Slider{\"amool\",\"bmpp\",\"cmqq\",\"dmrr\",\"emss\"}}"));
  REQUIRE(!parse_helper("Vertical{Slider{\"amool\", 0, 20, 100, 2}}"));
  REQUIRE(!parse_helper("Horizontal_{_Button{\"amool\",\"bmpp\",Simple}_}"));
  REQUIRE(!parse_helper("\"amool\"{Button{\"amool,\"bmpp\",Simple}}"));
  REQUIRE(!parse_helper("Vertical{Button{\"amool\" . \"bmpp\" . Ascii}}"));
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
                            str z\
                            Button{\"amool\",\"bmpp\", Ascii}\
                            Button{\"amool\",System(\"ls\"), Animated, z}      \
                            Horizontal{\
                                int x                                   \
                                int y                                   \
                                Slider{\"amool\", x, 1, 100, 10}        \
                                Slider{\"amool\", y, 1, 200, 100}}      \
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
        int a\
        Slider{\"amool\", a, 1, 100, 1}  \
        Button{\"amool\" , \"bmpp\", Animated}  \
        }"));

  REQUIRE(parse_helper("Vertical{\
        int a\
        Dropdown{[\"Physics\", \"Maths\", \"Chemistry\", \"Biology\",], a}  \
        Button{\"amool\" , \"bmpp\", Animated}  \
        }"));
  REQUIRE(parse_helper("Vertical{\
        int a = 20\
        Slider{\"amool\" ,a, 1, 100, 1}  \
        Button{\"amool\" , System(\"bmpp\"), Ascii}  \
        int b = 0\
        Menu{[\"Physics\",  \"Maths\",  \"Chemistry\",  \"Biology\",], b}  \
        }"));
}

TEST_CASE("Parse Recursive") {
  // expect pass
  REQUIRE(parse_helper("Vertical{\
        Button{\"amool\",\"bmpp\", Animated}  \
        Button{\"amool\",\"bmpp\", Simple}  \
        str x\
        Button{\"amool\",System(\"mkdir dir1\"), x}  \
        Horizontal{\
            int a = 40\
            Slider{\"amool\", a, 1, 100, 10}  \
            int b = 10\
            Slider{\"amool\", b, 1, 200, 100}  \
            int m = 0\
            Menu{[\"Physics\", \"Maths\",  \"Chemistry\",  \"Biology\",], m}  \
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
