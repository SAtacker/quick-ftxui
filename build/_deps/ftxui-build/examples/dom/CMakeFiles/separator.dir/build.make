# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/krishna/quick-ftxui

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/krishna/quick-ftxui/build

# Include any dependencies generated for this target.
include _deps/ftxui-build/examples/dom/CMakeFiles/separator.dir/depend.make

# Include the progress variables for this target.
include _deps/ftxui-build/examples/dom/CMakeFiles/separator.dir/progress.make

# Include the compile flags for this target's objects.
include _deps/ftxui-build/examples/dom/CMakeFiles/separator.dir/flags.make

_deps/ftxui-build/examples/dom/CMakeFiles/separator.dir/separator.cpp.o: _deps/ftxui-build/examples/dom/CMakeFiles/separator.dir/flags.make
_deps/ftxui-build/examples/dom/CMakeFiles/separator.dir/separator.cpp.o: _deps/ftxui-src/examples/dom/separator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/krishna/quick-ftxui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object _deps/ftxui-build/examples/dom/CMakeFiles/separator.dir/separator.cpp.o"
	cd /home/krishna/quick-ftxui/build/_deps/ftxui-build/examples/dom && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/separator.dir/separator.cpp.o -c /home/krishna/quick-ftxui/build/_deps/ftxui-src/examples/dom/separator.cpp

_deps/ftxui-build/examples/dom/CMakeFiles/separator.dir/separator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/separator.dir/separator.cpp.i"
	cd /home/krishna/quick-ftxui/build/_deps/ftxui-build/examples/dom && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/krishna/quick-ftxui/build/_deps/ftxui-src/examples/dom/separator.cpp > CMakeFiles/separator.dir/separator.cpp.i

_deps/ftxui-build/examples/dom/CMakeFiles/separator.dir/separator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/separator.dir/separator.cpp.s"
	cd /home/krishna/quick-ftxui/build/_deps/ftxui-build/examples/dom && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/krishna/quick-ftxui/build/_deps/ftxui-src/examples/dom/separator.cpp -o CMakeFiles/separator.dir/separator.cpp.s

# Object files for target separator
separator_OBJECTS = \
"CMakeFiles/separator.dir/separator.cpp.o"

# External object files for target separator
separator_EXTERNAL_OBJECTS =

_deps/ftxui-build/examples/dom/separator: _deps/ftxui-build/examples/dom/CMakeFiles/separator.dir/separator.cpp.o
_deps/ftxui-build/examples/dom/separator: _deps/ftxui-build/examples/dom/CMakeFiles/separator.dir/build.make
_deps/ftxui-build/examples/dom/separator: _deps/ftxui-build/ftxui-dom.a
_deps/ftxui-build/examples/dom/separator: _deps/ftxui-build/ftxui-screen.a
_deps/ftxui-build/examples/dom/separator: _deps/ftxui-build/examples/dom/CMakeFiles/separator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/krishna/quick-ftxui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable separator"
	cd /home/krishna/quick-ftxui/build/_deps/ftxui-build/examples/dom && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/separator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
_deps/ftxui-build/examples/dom/CMakeFiles/separator.dir/build: _deps/ftxui-build/examples/dom/separator

.PHONY : _deps/ftxui-build/examples/dom/CMakeFiles/separator.dir/build

_deps/ftxui-build/examples/dom/CMakeFiles/separator.dir/clean:
	cd /home/krishna/quick-ftxui/build/_deps/ftxui-build/examples/dom && $(CMAKE_COMMAND) -P CMakeFiles/separator.dir/cmake_clean.cmake
.PHONY : _deps/ftxui-build/examples/dom/CMakeFiles/separator.dir/clean

_deps/ftxui-build/examples/dom/CMakeFiles/separator.dir/depend:
	cd /home/krishna/quick-ftxui/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/krishna/quick-ftxui /home/krishna/quick-ftxui/build/_deps/ftxui-src/examples/dom /home/krishna/quick-ftxui/build /home/krishna/quick-ftxui/build/_deps/ftxui-build/examples/dom /home/krishna/quick-ftxui/build/_deps/ftxui-build/examples/dom/CMakeFiles/separator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/ftxui-build/examples/dom/CMakeFiles/separator.dir/depend

