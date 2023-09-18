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
  REQUIRE(parse_helper("Vertical{Red Button{\"amool\",\"bmpp\",Ascii}}"));
  REQUIRE(parse_helper("Vertical{Button{\"amool\",\"bmpp\",Simple}}"));
  REQUIRE(parse_helper(
      "Vertical{YellowLight Button{\"amool\",\"bmpp\",Animated}}"));
  REQUIRE(parse_helper("Vertical{Button{\"amool\",\"bmpp\"}}"));
  REQUIRE(
      parse_helper("Vertical{str x Blue Button{\"amool\",System(\"ls\"), x}}"));
  REQUIRE(parse_helper("Horizontal{Button{\"amool\",\"bmpp\",Ascii}}"));
  REQUIRE(parse_helper("Horizontal{Cyan Button{\"amool\",\"bmpp\",Simple}}"));
  REQUIRE(parse_helper("Horizontal{Button{\"amool\",\"bmpp\",Animated}}"));
  REQUIRE(parse_helper("Horizontal{CyanLight Button{\"amool\",\"bmpp\"}}"));
  REQUIRE(parse_helper(
      "Horizontal{str y Button{\"amool\",System(\"mkdir dir1\"), y}}"));

  REQUIRE(
      parse_helper("Vertical{int x Black Slider{\"amool\", x, 5, 100, 1}}"));
  REQUIRE(parse_helper("Horizontal{int y Slider{\"amool\", y, 5, 100, 1}}"));

  REQUIRE(parse_helper(
      "Horizontal{           White Button{          \"amool\"    ,       "
      "\"bmpp\"    ,       Simple }           }"));
  REQUIRE(
      parse_helper("Vertical{           Button{          \"amool\"    ,       "
                   "\"bmpp\"    ,       Simple }           }"));

  REQUIRE(parse_helper("Vertical{int y Magenta Dropdown{[\"Physics\",  "
                       "\"Maths\",  \"Chemistry\", "
                       " \"Biology\",], y}}"));
  REQUIRE(
      parse_helper("Horizontal{int z Default Menu{[\"Physics\",  \"Maths\",  "
                   "\"Chemistry\",  \"Biology\",], z}}"));
  REQUIRE(parse_helper("Vertical{int opt Toggle{[\"Opt1\", \"Opt2\",], opt}}"));
  REQUIRE(parse_helper(
      "Horizontal{int a MagentaLight Toggle{[\"Opt1\", \"Opt2\",], a}}"));
  REQUIRE(parse_helper("Vertical{int b Toggle{[\"Opt1\", \"Opt2\",], b}}"));
  REQUIRE(parse_helper(
      "Horizontal{int x_ GrayDark Toggle{[\"Opt1\", \"Opt2\",], x_}}"));

  // expect fail
  REQUIRE(!parse_helper("\"amool\"{Button{\"amool\",\"bmpp\",\"cmqq\"}}"));
  REQUIRE(!parse_helper("\"amool\"{\"Red\" Button{\"amool\",\"bmpp\",Ascii}}"));
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
                            BlueLight Button{\"amool\",\"bmpp\",Simple}      \
                            Button{\"amool\",\"bmpp\",Ascii}      \
                            Horizontal{\
                                Red Button{\"amool\",\"bmpp\",Animated}      \
                                Button{\"amool\",System(\"mkdir dir1\")}}     \
                            }"));
  REQUIRE(parse_helper("Vertical{\
                            str z\
                            Blue Button{\"amool\",\"bmpp\", Ascii}\
                            Button{\"amool\",System(\"ls\"), Animated, z}      \
                            Horizontal{\
                                int x                                   \
                                int y                                   \
                                Magenta Slider{\"amool\", x, 1, 100, 10}        \
                                Slider{\"amool\", y, 1, 200, 100}}      \
                            }"));
  REQUIRE(parse_helper("Vertical{\
        str x \
        Button{\"amool\",\"bmpp\", Ascii, x}\
        }"));

  REQUIRE(parse_helper("Horizontal{\
        Yellow Button{\"amool\",\"bmpp\",Ascii}\
        }"));
}

TEST_CASE("Parse Multiple Components in any order") {
  REQUIRE(parse_helper("Horizontal{\
        int a\
        Default Slider{\"amool\", a, 1, 100, 1}  \
        Button{\"amool\" , \"bmpp\", Animated}  \
        }"));

  REQUIRE(parse_helper("Vertical{\
        int a\
        Red Dropdown{[\"Physics\", \"Maths\", \"Chemistry\", \"Biology\",], a}  \
        str x\
        Magenta Button{\"amool\" , \"bmpp\", Animated, x}  \
        }"));
  REQUIRE(parse_helper("Vertical{\
        int a = 20\
        Slider{\"amool\" ,a, 1, 100, 1}  \
        Button{\"amool\" , System(\"bmpp\"), Ascii}  \
        int b = 0\
        Black Menu{[\"Physics\",  \"Maths\",  \"Chemistry\",  \"Biology\",], HorizontalAnimated, b}  \
        }"));
}

TEST_CASE("Parse Recursive") {
  // expect pass
  REQUIRE(parse_helper("Vertical{\
        YellowLight Button{\"amool\",\"bmpp\", Animated}  \
        Button{\"amool\",\"bmpp\", Simple}  \
        str x\
        Button{\"amool\",System(\"mkdir dir1\"), x}  \
        Horizontal{\
            int a = 40\
            Blue Slider{\"amool\", a, 1, 100, 10}  \
            int b = 10\
            Slider{\"amool\", b, 1, 200, 100}  \
            int m = 0\
            RedLight Menu{[\"Physics\", \"Maths\",  \"Chemistry\",  \"Biology\",], m}  \
            Vertical{\
                Button{\"amool\",\"bmpp\", Ascii}  \
                Button{\"amool\",System(\"ls\"), Animated}  \
            }  \
        }  \
    }"));

  // expect fail
  REQUIRE(!parse_helper("Vertical{\
        red Button{\"amool\",\"bmpp\",Ascii               \
            Button{\"amool\",\"bmpp\",\"cmqq\"}          \
        }\
        }"));

  REQUIRE(!parse_helper("Horizontal{\
        Button{\"amool\",\"bmpp\" Animated             \
            blue Button{\"amool\",\"bmpp\" Ascii}          \
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

TEST_CASE("Parse DOM elements") {
  REQUIRE(parse_helper("Vertical {\
        Text(\"Hello World\")       \
        separator                   \
        Paragraph(\"Hello to his paragraph\")\
        HeavyBorder Horizontal {    \
            RedLight dim Text(\"amool\") \
        }\
    }"));

  // Parse text and its styles
  REQUIRE(parse_helper("Vertical {\
        Blue Text(\"Hello World\")  \
        Red bold Text(\"amool\")    \
        dim Text(\"bmpp\")          \
        underlined Text(\"cmqq\")   \
        Magenta underlinedDouble Text(\"dmrr\") \
        blink Text(\"emss\")        \
        Red inverted Text(\"This has an inverted look\")    \
        strikethrough Text(\"This is strikethrough\")   \
    }"));

  REQUIRE(!parse_helper("Vertical {\
        blue Text(\"Hello World\")  \
        Bold Red Text(\"amool\")    \
        DIM Text(\"bmpp\")          \
        underlined Text(cmqq)   \
        underlinedDouble Magenta Text(\"dmrr\") \
        blink Text(123)        \
        inverted Red Text(\"This has an inverted look\")    \
        strikethrough Text(\"This is strikethrough\")   \
    }"));

  // Paragraphs, separators and borders
  REQUIRE(parse_helper("HeavyBorder Vertical {\
        Paragraph(\"I guess I should have talked before going into the unknown\")\
        separator   \
        Paragraph(\"Lorem ipsum dolor sit amet, consectetur adipiscing elit,    \
            sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.      \
            Ut enim ad minim veniam, quis nostrud exercitation ullamco          \
            laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure    \
            dolor in reprehenderit in voluptate velit esse cillum dolore    \
            eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat     \
            non proident, sunt in culpa qui officia deserunt mollit anim    \
            id est laborum.\")  \
        Dashed separator        \
        Border Horizontal {     \
            Paragraph(\"This is my peace offering.\")     \
        }\
    }"));

  REQUIRE(!parse_helper("Heavy Border Vertical {\
        Paragraph(\"I guess I should have talked before going into the unknown\")\
        separator   \
        Paragraph(\"Lorem ipsum dolor sit amet, consectetur adipiscing elit,    \
            sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.      \
            Ut enim ad minim veniam, quis nostrud exercitation ullamco          \
            laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure    \
            dolor in reprehenderit in voluptate velit esse cillum dolore    \
            eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat     \
            non proident, sunt in culpa qui officia deserunt mollit anim    \
            id est laborum.\")  \
        dashed separator        \
        Paragraph(This is my peace offering)     \
    }"));
}

TEST_CASE("Parse Components and DOM together") {
  REQUIRE(parse_helper("HeavyBorder Vertical {\
        int x                                   \
        Blue Slider{                            \
            \"amool\",                          \
            x,                                  \
            0,                                  \
            30,                                 \
            2                                   \
        }                                       \
        Double separator                        \
        LightBorder Horizontal {                \
            Yellow dim Text(\"bmpp\")           \
        }                                       \
        str y                                   \
        Button {                                \
            \"amool\",                          \
            System(\"ls -l\"),                  \
            y                                   \
        }                                       \
    }"));

  REQUIRE(parse_helper("DashedBorder Vertical{\
        int x                                   \
        Blue Dropdown{                          \
            [\"amool\", \"bmpp\", \"cmqq\",],   \
            x                                   \
        }                                       \
        Light separator                         \
        RoundedBorder Horizontal {              \
            Yellow strikethrough Text(\"dmrr\") \
        }                                       \
        str y                                   \
        Button {                                \
            \"amool\",                          \
            System(\"ls -l\"),                  \
            Animated,                            \
            y                                   \
        }                                       \
    }"));

  REQUIRE(!parse_helper("Heavy Border Vertical {\
        int x                                   \
        Blue Slider{                            \
            \"amool\",                          \
            x,                                  \
            0,                                  \
            30,                                 \
            2                                   \
        }                                       \
        Double Separator                        \
        Horizontal {                \
            LightBorder Yellow dim Text(\"bmpp\")           \
        }                                       \
        str y                                   \
        Button {                                \
            \"amool\",                          \
            System(\"ls -l\"),                  \
            y                                   \
        }                                       \
    }"));
}
