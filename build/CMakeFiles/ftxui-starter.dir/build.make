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
include CMakeFiles/ftxui-starter.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ftxui-starter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ftxui-starter.dir/flags.make

# Object files for target ftxui-starter
ftxui__starter_OBJECTS =

# External object files for target ftxui-starter
ftxui__starter_EXTERNAL_OBJECTS =

ftxui-starter: CMakeFiles/ftxui-starter.dir/build.make
ftxui-starter: _deps/ftxui-build/ftxui-screen.a
ftxui-starter: _deps/ftxui-build/ftxui-dom.a
ftxui-starter: _deps/ftxui-build/ftxui-component.a
ftxui-starter: _deps/ftxui-build/ftxui-dom.a
ftxui-starter: _deps/ftxui-build/ftxui-screen.a
ftxui-starter: CMakeFiles/ftxui-starter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/krishna/quick-ftxui/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Linking CXX executable ftxui-starter"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ftxui-starter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ftxui-starter.dir/build: ftxui-starter

.PHONY : CMakeFiles/ftxui-starter.dir/build

CMakeFiles/ftxui-starter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ftxui-starter.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ftxui-starter.dir/clean

CMakeFiles/ftxui-starter.dir/depend:
	cd /home/krishna/quick-ftxui/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/krishna/quick-ftxui /home/krishna/quick-ftxui /home/krishna/quick-ftxui/build /home/krishna/quick-ftxui/build /home/krishna/quick-ftxui/build/CMakeFiles/ftxui-starter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ftxui-starter.dir/depend

