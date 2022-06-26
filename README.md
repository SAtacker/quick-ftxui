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
