#include "quick-ftxui.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace quick_ftxui;

int main() {

  set_int_var("x", 5);
  set_str_var("y", "");
  string source_code = R"(Vertical{
        str z = "init"
        str a
        int o = 0
        Input {
            "Type something...",
            Password,
            y
        }
        Slider {
            "Test: ",
            x,
            0,
            100,
            2
        }
        Magenta Button{
            "ls",
            System("/usr/bin/google-chrome-stable"),
            Ascii,
            z
        }
        Menu{
            [ "Physics",  "Maths",  "Chemistry",  "Biology",],
            VerticalAnimated,
            o
        }
        Button {
            "Exit",
            "Exit"
        }
    })";

  parse_qf(source_code);

  cout << "x is: " << get_int("x") << "\n";
  cout << "y is: " << get_str("y") << "\n";
  cout << "o is: " << get_int("o") << "\n";
  cout << "z is: " << get_str("z") << "\n";
}