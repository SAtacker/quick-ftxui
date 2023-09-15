<div align="center">
    <img src="./assets/qf-high-resolution-color-logo.png" height=150 width=200></img>
    <h1>Quick-FTXUI</h1>
    <h3>A <i>Quick</i> & Easy way to render terminal user interfaces, using FTXUI.</h3>
</div>

## Example

It converts this JSON-like [code](./examples/multiple_components.qf) into a TUI

```
Vertical{
    str x
    Blue Button{
        "Open firefox",
        System("/usr/bin/firefox"),
        Animated,
        x
    }
    int y = 20
    Yellow Slider {
        "A Slider",
        y,
        0,
        100,
        1
    }
    Horizontal {
        int z = 1
        int w
        Red Dropdown {
            [ "Zain", "Mahesh", "Alqama", "Vaidic", "Mundane", "Advait", ],
            z
        }
        Cyan Toggle {
            [ "On", "Off", ],
            w
        }
    }

    RedLight Button {
        "Exit",
        "Exit",
        Ascii
    }
}
```

### Output

https://github.com/vrnimje/quick-ftxui/assets/103848930/c0d92edb-79fe-434d-9d72-0a577f617ed5

## Features
* #### Supports majority of FTXUI components, listed below:
    <details><summary>Button</summary>
    Supports System() calls (like /usr/bin/firefox)

    [Example](./examples/Button.qf)

    ![](./assets/image-1.png)
    </details>

    <details><summary>Slider</summary>

    [Example](./examples/Slider.qf)

    ![](./assets/image-2.png)

    </details>

    <details><summary>Input</summary>

    [Example](./examples/input.qf)

    ![](./assets/image-4.png)

    </details>

    <details><summary>Dropdown</summary>

    [Example](./examples/menu_toggle_dropdown.qf#L15-L18)

    ![](./assets/image-5.png)

    </details>

    <details><summary>Menu</summary>

    [Example](./examples/menu_toggle_dropdown.qf#L4-L8)
    
    ![](./assets/image-6.png)

    </details>

    <details><summary>Toggle</summary>

    [Example](./examples/menu_toggle_dropdown.qf#L11-14)

    ![](./assets/image-7.png)

    </details>
    <br>

    **Note:** To run these examples, build this repository with the steps mentioned [here](#build-instructions)

* #### Variables

    Used as hooks, so that we can obtain the input given to the GUI. Currenlty, supports `int` and `str` data types

    Check out the examples in [this directory](./examples/)

    **Note:** To run these examples, build this repository with the steps mentioned [here](#build-instructions)

* #### Embedded scripting supported in C++

    Supports basic scripting functionality, with functions to add & access the quick-ftxui variables.
    
    [Full Example](./cpp_examples/example.cpp)

    ```cpp
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
            Button{
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
    ```

    **Note:** To run this above example, build this repository with examples, steps [given here](#build-with-examples)

## Build instructions:
~~~bash
mkdir build
cd build
cmake .. -G "Ninja" -DQUICK_FTXUI_TESTS=ON
ninja
./quick-ftxui ../examples/Button.qf
~~~

## Build with examples:
~~~bash
mkdir build
cd build
cmake .. -G "Ninja" -DQUICK_FTXUI_EXAMPLES=ON
ninja
./cpp_examples/quick_ftxui_example
~~~

## Roadmap for v0.2 release

- [x] Adding color (component wise)
- [ ] Adding FTXUI DOM elements (e.g. seperator)
- [ ] Adding a way to use C++ defined variables directly, instead of depending on script-variables 
- [ ] Adding detailed user documentation

## Dependencies

* [FTXUI](https://github.com/ArthurSonzogni/FTXUI), by [Arthur Sonzogni](https://github.com/ArthurSonzogni), for rendering the terminal graphics in backend
* [Boost Spirit](https://github.com/boostorg/spirit), for writing the parser for the custom language

## Acknowledgements

* Special Thanks to [Shreyas Atre](https://github.com/SAtacker) and [Krishna Narayanan](https://github.com/Krishna-13-cyber) for their very crucial [foundational work](https://github.com/SAtacker/quick-ftxui) and guidance.
* Thanks to [Prit Kanadiya](https://github.com/PritK99) and [Khushi Balia](https://github.com/Khushi-Balia) for their contributions to the rest of the codebase
* Thanks to [Arthur Sonzogni](https://github.com/ArthurSonzogni) for his [FTXUI starter repository template](https://github.com/ArthurSonzogni/ftxui-starter), and his amazing FTXUI library 

## Disclaimer: This project is still in development phase, use it with caution. Future releases may break some functionality






