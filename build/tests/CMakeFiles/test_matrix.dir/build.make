# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dominik/Documents/scientific_computing/first_git/ASC-bla

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dominik/Documents/scientific_computing/first_git/ASC-bla/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/test_matrix.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/test_matrix.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/test_matrix.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/test_matrix.dir/flags.make

tests/CMakeFiles/test_matrix.dir/test_matrix.cc.o: tests/CMakeFiles/test_matrix.dir/flags.make
tests/CMakeFiles/test_matrix.dir/test_matrix.cc.o: ../tests/test_matrix.cc
tests/CMakeFiles/test_matrix.dir/test_matrix.cc.o: tests/CMakeFiles/test_matrix.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dominik/Documents/scientific_computing/first_git/ASC-bla/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/test_matrix.dir/test_matrix.cc.o"
	cd /home/dominik/Documents/scientific_computing/first_git/ASC-bla/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/test_matrix.dir/test_matrix.cc.o -MF CMakeFiles/test_matrix.dir/test_matrix.cc.o.d -o CMakeFiles/test_matrix.dir/test_matrix.cc.o -c /home/dominik/Documents/scientific_computing/first_git/ASC-bla/tests/test_matrix.cc

tests/CMakeFiles/test_matrix.dir/test_matrix.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_matrix.dir/test_matrix.cc.i"
	cd /home/dominik/Documents/scientific_computing/first_git/ASC-bla/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dominik/Documents/scientific_computing/first_git/ASC-bla/tests/test_matrix.cc > CMakeFiles/test_matrix.dir/test_matrix.cc.i

tests/CMakeFiles/test_matrix.dir/test_matrix.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_matrix.dir/test_matrix.cc.s"
	cd /home/dominik/Documents/scientific_computing/first_git/ASC-bla/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dominik/Documents/scientific_computing/first_git/ASC-bla/tests/test_matrix.cc -o CMakeFiles/test_matrix.dir/test_matrix.cc.s

# Object files for target test_matrix
test_matrix_OBJECTS = \
"CMakeFiles/test_matrix.dir/test_matrix.cc.o"

# External object files for target test_matrix
test_matrix_EXTERNAL_OBJECTS =

tests/test_matrix: tests/CMakeFiles/test_matrix.dir/test_matrix.cc.o
tests/test_matrix: tests/CMakeFiles/test_matrix.dir/build.make
tests/test_matrix: tests/CMakeFiles/test_matrix.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dominik/Documents/scientific_computing/first_git/ASC-bla/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_matrix"
	cd /home/dominik/Documents/scientific_computing/first_git/ASC-bla/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_matrix.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/test_matrix.dir/build: tests/test_matrix
.PHONY : tests/CMakeFiles/test_matrix.dir/build

tests/CMakeFiles/test_matrix.dir/clean:
	cd /home/dominik/Documents/scientific_computing/first_git/ASC-bla/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/test_matrix.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/test_matrix.dir/clean

tests/CMakeFiles/test_matrix.dir/depend:
	cd /home/dominik/Documents/scientific_computing/first_git/ASC-bla/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dominik/Documents/scientific_computing/first_git/ASC-bla /home/dominik/Documents/scientific_computing/first_git/ASC-bla/tests /home/dominik/Documents/scientific_computing/first_git/ASC-bla/build /home/dominik/Documents/scientific_computing/first_git/ASC-bla/build/tests /home/dominik/Documents/scientific_computing/first_git/ASC-bla/build/tests/CMakeFiles/test_matrix.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/test_matrix.dir/depend

