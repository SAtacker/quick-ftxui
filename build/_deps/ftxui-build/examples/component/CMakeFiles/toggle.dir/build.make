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
include _deps/ftxui-build/examples/component/CMakeFiles/toggle.dir/depend.make

# Include the progress variables for this target.
include _deps/ftxui-build/examples/component/CMakeFiles/toggle.dir/progress.make

# Include the compile flags for this target's objects.
include _deps/ftxui-build/examples/component/CMakeFiles/toggle.dir/flags.make

_deps/ftxui-build/examples/component/CMakeFiles/toggle.dir/toggle.cpp.o: _deps/ftxui-build/examples/component/CMakeFiles/toggle.dir/flags.make
_deps/ftxui-build/examples/component/CMakeFiles/toggle.dir/toggle.cpp.o: _deps/ftxui-src/examples/component/toggle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/krishna/quick-ftxui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object _deps/ftxui-build/examples/component/CMakeFiles/toggle.dir/toggle.cpp.o"
	cd /home/krishna/quick-ftxui/build/_deps/ftxui-build/examples/component && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/toggle.dir/toggle.cpp.o -c /home/krishna/quick-ftxui/build/_deps/ftxui-src/examples/component/toggle.cpp

_deps/ftxui-build/examples/component/CMakeFiles/toggle.dir/toggle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/toggle.dir/toggle.cpp.i"
	cd /home/krishna/quick-ftxui/build/_deps/ftxui-build/examples/component && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/krishna/quick-ftxui/build/_deps/ftxui-src/examples/component/toggle.cpp > CMakeFiles/toggle.dir/toggle.cpp.i

_deps/ftxui-build/examples/component/CMakeFiles/toggle.dir/toggle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/toggle.dir/toggle.cpp.s"
	cd /home/krishna/quick-ftxui/build/_deps/ftxui-build/examples/component && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/krishna/quick-ftxui/build/_deps/ftxui-src/examples/component/toggle.cpp -o CMakeFiles/toggle.dir/toggle.cpp.s

# Object files for target toggle
toggle_OBJECTS = \
"CMakeFiles/toggle.dir/toggle.cpp.o"

# External object files for target toggle
toggle_EXTERNAL_OBJECTS =

_deps/ftxui-build/examples/component/toggle: _deps/ftxui-build/examples/component/CMakeFiles/toggle.dir/toggle.cpp.o
_deps/ftxui-build/examples/component/toggle: _deps/ftxui-build/examples/component/CMakeFiles/toggle.dir/build.make
_deps/ftxui-build/examples/component/toggle: _deps/ftxui-build/ftxui-component.a
_deps/ftxui-build/examples/component/toggle: _deps/ftxui-build/ftxui-dom.a
_deps/ftxui-build/examples/component/toggle: _deps/ftxui-build/ftxui-screen.a
_deps/ftxui-build/examples/component/toggle: _deps/ftxui-build/examples/component/CMakeFiles/toggle.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/krishna/quick-ftxui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable toggle"
	cd /home/krishna/quick-ftxui/build/_deps/ftxui-build/examples/component && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/toggle.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
_deps/ftxui-build/examples/component/CMakeFiles/toggle.dir/build: _deps/ftxui-build/examples/component/toggle

.PHONY : _deps/ftxui-build/examples/component/CMakeFiles/toggle.dir/build

_deps/ftxui-build/examples/component/CMakeFiles/toggle.dir/clean:
	cd /home/krishna/quick-ftxui/build/_deps/ftxui-build/examples/component && $(CMAKE_COMMAND) -P CMakeFiles/toggle.dir/cmake_clean.cmake
.PHONY : _deps/ftxui-build/examples/component/CMakeFiles/toggle.dir/clean

_deps/ftxui-build/examples/component/CMakeFiles/toggle.dir/depend:
	cd /home/krishna/quick-ftxui/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/krishna/quick-ftxui /home/krishna/quick-ftxui/build/_deps/ftxui-src/examples/component /home/krishna/quick-ftxui/build /home/krishna/quick-ftxui/build/_deps/ftxui-build/examples/component /home/krishna/quick-ftxui/build/_deps/ftxui-build/examples/component/CMakeFiles/toggle.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/ftxui-build/examples/component/CMakeFiles/toggle.dir/depend

