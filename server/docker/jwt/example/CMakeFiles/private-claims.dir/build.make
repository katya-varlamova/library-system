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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.22.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.22.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/kate/Desktop/jwt-cpp-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/kate/Desktop/jwt-cpp-master

# Include any dependencies generated for this target.
include example/CMakeFiles/private-claims.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include example/CMakeFiles/private-claims.dir/compiler_depend.make

# Include the progress variables for this target.
include example/CMakeFiles/private-claims.dir/progress.make

# Include the compile flags for this target's objects.
include example/CMakeFiles/private-claims.dir/flags.make

example/CMakeFiles/private-claims.dir/private-claims.cpp.o: example/CMakeFiles/private-claims.dir/flags.make
example/CMakeFiles/private-claims.dir/private-claims.cpp.o: example/private-claims.cpp
example/CMakeFiles/private-claims.dir/private-claims.cpp.o: example/CMakeFiles/private-claims.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kate/Desktop/jwt-cpp-master/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object example/CMakeFiles/private-claims.dir/private-claims.cpp.o"
	cd /Users/kate/Desktop/jwt-cpp-master/example && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT example/CMakeFiles/private-claims.dir/private-claims.cpp.o -MF CMakeFiles/private-claims.dir/private-claims.cpp.o.d -o CMakeFiles/private-claims.dir/private-claims.cpp.o -c /Users/kate/Desktop/jwt-cpp-master/example/private-claims.cpp

example/CMakeFiles/private-claims.dir/private-claims.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/private-claims.dir/private-claims.cpp.i"
	cd /Users/kate/Desktop/jwt-cpp-master/example && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kate/Desktop/jwt-cpp-master/example/private-claims.cpp > CMakeFiles/private-claims.dir/private-claims.cpp.i

example/CMakeFiles/private-claims.dir/private-claims.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/private-claims.dir/private-claims.cpp.s"
	cd /Users/kate/Desktop/jwt-cpp-master/example && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kate/Desktop/jwt-cpp-master/example/private-claims.cpp -o CMakeFiles/private-claims.dir/private-claims.cpp.s

# Object files for target private-claims
private__claims_OBJECTS = \
"CMakeFiles/private-claims.dir/private-claims.cpp.o"

# External object files for target private-claims
private__claims_EXTERNAL_OBJECTS =

example/private-claims: example/CMakeFiles/private-claims.dir/private-claims.cpp.o
example/private-claims: example/CMakeFiles/private-claims.dir/build.make
example/private-claims: /opt/local/lib/libssl.dylib
example/private-claims: /opt/local/lib/libcrypto.dylib
example/private-claims: example/CMakeFiles/private-claims.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/kate/Desktop/jwt-cpp-master/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable private-claims"
	cd /Users/kate/Desktop/jwt-cpp-master/example && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/private-claims.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
example/CMakeFiles/private-claims.dir/build: example/private-claims
.PHONY : example/CMakeFiles/private-claims.dir/build

example/CMakeFiles/private-claims.dir/clean:
	cd /Users/kate/Desktop/jwt-cpp-master/example && $(CMAKE_COMMAND) -P CMakeFiles/private-claims.dir/cmake_clean.cmake
.PHONY : example/CMakeFiles/private-claims.dir/clean

example/CMakeFiles/private-claims.dir/depend:
	cd /Users/kate/Desktop/jwt-cpp-master && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/kate/Desktop/jwt-cpp-master /Users/kate/Desktop/jwt-cpp-master/example /Users/kate/Desktop/jwt-cpp-master /Users/kate/Desktop/jwt-cpp-master/example /Users/kate/Desktop/jwt-cpp-master/example/CMakeFiles/private-claims.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : example/CMakeFiles/private-claims.dir/depend
