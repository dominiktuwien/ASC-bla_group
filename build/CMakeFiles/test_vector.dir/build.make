# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = "C:/Program Files/CMake/bin/cmake.exe"

# The command to remove a file.
RM = "C:/Program Files/CMake/bin/cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:/Felix/ESC/ASC-bla_group

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:/Felix/ESC/ASC-bla_group/build

# Include any dependencies generated for this target.
include CMakeFiles/test_vector.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test_vector.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test_vector.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_vector.dir/flags.make

CMakeFiles/test_vector.dir/tests/test_vector.cc.obj: CMakeFiles/test_vector.dir/flags.make
CMakeFiles/test_vector.dir/tests/test_vector.cc.obj: CMakeFiles/test_vector.dir/includes_CXX.rsp
CMakeFiles/test_vector.dir/tests/test_vector.cc.obj: C:/Felix/ESC/ASC-bla_group/tests/test_vector.cc
CMakeFiles/test_vector.dir/tests/test_vector.cc.obj: CMakeFiles/test_vector.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:/Felix/ESC/ASC-bla_group/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_vector.dir/tests/test_vector.cc.obj"
	C:/Strawberry/c/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_vector.dir/tests/test_vector.cc.obj -MF CMakeFiles/test_vector.dir/tests/test_vector.cc.obj.d -o CMakeFiles/test_vector.dir/tests/test_vector.cc.obj -c C:/Felix/ESC/ASC-bla_group/tests/test_vector.cc

CMakeFiles/test_vector.dir/tests/test_vector.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test_vector.dir/tests/test_vector.cc.i"
	C:/Strawberry/c/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:/Felix/ESC/ASC-bla_group/tests/test_vector.cc > CMakeFiles/test_vector.dir/tests/test_vector.cc.i

CMakeFiles/test_vector.dir/tests/test_vector.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test_vector.dir/tests/test_vector.cc.s"
	C:/Strawberry/c/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:/Felix/ESC/ASC-bla_group/tests/test_vector.cc -o CMakeFiles/test_vector.dir/tests/test_vector.cc.s

# Object files for target test_vector
test_vector_OBJECTS = \
"CMakeFiles/test_vector.dir/tests/test_vector.cc.obj"

# External object files for target test_vector
test_vector_EXTERNAL_OBJECTS =

test_vector.exe: CMakeFiles/test_vector.dir/tests/test_vector.cc.obj
test_vector.exe: CMakeFiles/test_vector.dir/build.make
test_vector.exe: CMakeFiles/test_vector.dir/linkLibs.rsp
test_vector.exe: CMakeFiles/test_vector.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:/Felix/ESC/ASC-bla_group/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_vector.exe"
	"C:/Program Files/CMake/bin/cmake.exe" -E rm -f CMakeFiles/test_vector.dir/objects.a
	C:/Strawberry/c/bin/ar.exe qc CMakeFiles/test_vector.dir/objects.a @CMakeFiles/test_vector.dir/objects1.rsp
	C:/Strawberry/c/bin/g++.exe -g -Wl,--whole-archive CMakeFiles/test_vector.dir/objects.a -Wl,--no-whole-archive -o test_vector.exe -Wl,--out-implib,libtest_vector.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/test_vector.dir/linkLibs.rsp

# Rule to build all files generated by this target.
CMakeFiles/test_vector.dir/build: test_vector.exe
.PHONY : CMakeFiles/test_vector.dir/build

CMakeFiles/test_vector.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_vector.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_vector.dir/clean

CMakeFiles/test_vector.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" C:/Felix/ESC/ASC-bla_group C:/Felix/ESC/ASC-bla_group C:/Felix/ESC/ASC-bla_group/build C:/Felix/ESC/ASC-bla_group/build C:/Felix/ESC/ASC-bla_group/build/CMakeFiles/test_vector.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/test_vector.dir/depend

