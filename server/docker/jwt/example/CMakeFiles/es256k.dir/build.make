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
include example/CMakeFiles/es256k.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include example/CMakeFiles/es256k.dir/compiler_depend.make

# Include the progress variables for this target.
include example/CMakeFiles/es256k.dir/progress.make

# Include the compile flags for this target's objects.
include example/CMakeFiles/es256k.dir/flags.make

example/CMakeFiles/es256k.dir/es256k.cpp.o: example/CMakeFiles/es256k.dir/flags.make
example/CMakeFiles/es256k.dir/es256k.cpp.o: example/es256k.cpp
example/CMakeFiles/es256k.dir/es256k.cpp.o: example/CMakeFiles/es256k.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kate/Desktop/jwt-cpp-master/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object example/CMakeFiles/es256k.dir/es256k.cpp.o"
	cd /Users/kate/Desktop/jwt-cpp-master/example && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT example/CMakeFiles/es256k.dir/es256k.cpp.o -MF CMakeFiles/es256k.dir/es256k.cpp.o.d -o CMakeFiles/es256k.dir/es256k.cpp.o -c /Users/kate/Desktop/jwt-cpp-master/example/es256k.cpp

example/CMakeFiles/es256k.dir/es256k.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/es256k.dir/es256k.cpp.i"
	cd /Users/kate/Desktop/jwt-cpp-master/example && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kate/Desktop/jwt-cpp-master/example/es256k.cpp > CMakeFiles/es256k.dir/es256k.cpp.i

example/CMakeFiles/es256k.dir/es256k.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/es256k.dir/es256k.cpp.s"
	cd /Users/kate/Desktop/jwt-cpp-master/example && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kate/Desktop/jwt-cpp-master/example/es256k.cpp -o CMakeFiles/es256k.dir/es256k.cpp.s

# Object files for target es256k
es256k_OBJECTS = \
"CMakeFiles/es256k.dir/es256k.cpp.o"

# External object files for target es256k
es256k_EXTERNAL_OBJECTS =

example/es256k: example/CMakeFiles/es256k.dir/es256k.cpp.o
example/es256k: example/CMakeFiles/es256k.dir/build.make
example/es256k: /opt/local/lib/libssl.dylib
example/es256k: /opt/local/lib/libcrypto.dylib
example/es256k: example/CMakeFiles/es256k.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/kate/Desktop/jwt-cpp-master/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable es256k"
	cd /Users/kate/Desktop/jwt-cpp-master/example && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/es256k.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
example/CMakeFiles/es256k.dir/build: example/es256k
.PHONY : example/CMakeFiles/es256k.dir/build

example/CMakeFiles/es256k.dir/clean:
	cd /Users/kate/Desktop/jwt-cpp-master/example && $(CMAKE_COMMAND) -P CMakeFiles/es256k.dir/cmake_clean.cmake
.PHONY : example/CMakeFiles/es256k.dir/clean

example/CMakeFiles/es256k.dir/depend:
	cd /Users/kate/Desktop/jwt-cpp-master && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/kate/Desktop/jwt-cpp-master /Users/kate/Desktop/jwt-cpp-master/example /Users/kate/Desktop/jwt-cpp-master /Users/kate/Desktop/jwt-cpp-master/example /Users/kate/Desktop/jwt-cpp-master/example/CMakeFiles/es256k.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : example/CMakeFiles/es256k.dir/depend

