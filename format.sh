#!/bin/sh
find . -iname *.h -o -iname *.c -o -iname *.cpp -o -iname *.hpp \
    | xargs clang-format-17 -style=file -i -fallback-style=none