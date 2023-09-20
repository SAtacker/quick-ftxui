#include "quick-ftxui.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace quick_ftxui;

int main() {
  int x = 5;
  string y = "Init value";
  set_int_var("x", &x);
  set_str_var("y", &y);
  string source_code = R"(Border Vertical{
        str z = "init"
        str a
        int o = 0
        Input {
            "Type something...",
            y
        }
        RedLight Slider {
            "Test: ",
            x,
            0,
            100,
            2
        }
        Magenta Button{
            "Chrome",
            System("/usr/bin/google-chrome-stable"),
            Animated,
            z
        }
        Green Menu{
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

  cout << "Slider value is: " << x << "\n";
  cout << "User input is: " << y << "\n";
  cout << "Option no. selected in Menu is: " << get_int("o") + 1 << "\n";
  cout << "Chrome debug msgs are: " << get_str("z") << "\n";
}