Quick-FTXUI
-------------

[![Linux Build](https://github.com/SAtacker/quick-ftxui/actions/workflows/linux_build.yml/badge.svg)](https://github.com/SAtacker/quick-ftxui/actions/workflows/linux_build.yml)
[![Windows Build](https://github.com/SAtacker/quick-ftxui/actions/workflows/windows_build.yml/badge.svg)](https://github.com/SAtacker/quick-ftxui/actions/workflows/windows_build.yml)


# Build instructions:
~~~bash
mkdir build
cd build
cmake .. -G "Ninja" -DQUICK_FTXUI_TESTS=ON
ninja
./quick-ftxui
~~~

## Linux snap build:
Upload your game to github and visit https://snapcraft.io/build.

## Status

It can parse the following code
```
{
    Button{
        "arg1",
        "arg2"
    }
}
```

[![asciicast](https://asciinema.org/a/537702.svg)](https://asciinema.org/a/537702)

## How it should look like

- `Button`, `Exit` are identifiers
- `Button` is a `component` type
- `|` is a `decorator` operator
- `Blue` is a decorator
- The operation `plain | decorator` returns `nice` type
- `render` is like a main function, just render the component

Grammar
```
nice -> plain | (nice >> decorator_op >> decorator)

```

```
my_component = Button("Nothing",Exit) | Blue
render my_component
```
