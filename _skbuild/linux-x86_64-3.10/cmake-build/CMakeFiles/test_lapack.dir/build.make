# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /tmp/pip-build-env-uhh6i6jk/overlay/local/lib/python3.10/dist-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /tmp/pip-build-env-uhh6i6jk/overlay/local/lib/python3.10/dist-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dominik/Documents/scientific_computing/first_project/ASC-bla_group

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dominik/Documents/scientific_computing/first_project/ASC-bla_group/_skbuild/linux-x86_64-3.10/cmake-build

# Include any dependencies generated for this target.
include CMakeFiles/test_lapack.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test_lapack.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test_lapack.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_lapack.dir/flags.make

CMakeFiles/test_lapack.dir/tests/test_lapack.cc.o: CMakeFiles/test_lapack.dir/flags.make
CMakeFiles/test_lapack.dir/tests/test_lapack.cc.o: /home/dominik/Documents/scientific_computing/first_project/ASC-bla_group/tests/test_lapack.cc
CMakeFiles/test_lapack.dir/tests/test_lapack.cc.o: CMakeFiles/test_lapack.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/dominik/Documents/scientific_computing/first_project/ASC-bla_group/_skbuild/linux-x86_64-3.10/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_lapack.dir/tests/test_lapack.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_lapack.dir/tests/test_lapack.cc.o -MF CMakeFiles/test_lapack.dir/tests/test_lapack.cc.o.d -o CMakeFiles/test_lapack.dir/tests/test_lapack.cc.o -c /home/dominik/Documents/scientific_computing/first_project/ASC-bla_group/tests/test_lapack.cc

CMakeFiles/test_lapack.dir/tests/test_lapack.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test_lapack.dir/tests/test_lapack.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dominik/Documents/scientific_computing/first_project/ASC-bla_group/tests/test_lapack.cc > CMakeFiles/test_lapack.dir/tests/test_lapack.cc.i

CMakeFiles/test_lapack.dir/tests/test_lapack.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test_lapack.dir/tests/test_lapack.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dominik/Documents/scientific_computing/first_project/ASC-bla_group/tests/test_lapack.cc -o CMakeFiles/test_lapack.dir/tests/test_lapack.cc.s

# Object files for target test_lapack
test_lapack_OBJECTS = \
"CMakeFiles/test_lapack.dir/tests/test_lapack.cc.o"

# External object files for target test_lapack
test_lapack_EXTERNAL_OBJECTS =

test_lapack: CMakeFiles/test_lapack.dir/tests/test_lapack.cc.o
test_lapack: CMakeFiles/test_lapack.dir/build.make
test_lapack: /usr/lib/x86_64-linux-gnu/liblapack.so
test_lapack: /usr/lib/x86_64-linux-gnu/libblas.so
test_lapack: CMakeFiles/test_lapack.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/dominik/Documents/scientific_computing/first_project/ASC-bla_group/_skbuild/linux-x86_64-3.10/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_lapack"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_lapack.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_lapack.dir/build: test_lapack
.PHONY : CMakeFiles/test_lapack.dir/build

CMakeFiles/test_lapack.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_lapack.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_lapack.dir/clean

CMakeFiles/test_lapack.dir/depend:
	cd /home/dominik/Documents/scientific_computing/first_project/ASC-bla_group/_skbuild/linux-x86_64-3.10/cmake-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dominik/Documents/scientific_computing/first_project/ASC-bla_group /home/dominik/Documents/scientific_computing/first_project/ASC-bla_group /home/dominik/Documents/scientific_computing/first_project/ASC-bla_group/_skbuild/linux-x86_64-3.10/cmake-build /home/dominik/Documents/scientific_computing/first_project/ASC-bla_group/_skbuild/linux-x86_64-3.10/cmake-build /home/dominik/Documents/scientific_computing/first_project/ASC-bla_group/_skbuild/linux-x86_64-3.10/cmake-build/CMakeFiles/test_lapack.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/test_lapack.dir/depend

