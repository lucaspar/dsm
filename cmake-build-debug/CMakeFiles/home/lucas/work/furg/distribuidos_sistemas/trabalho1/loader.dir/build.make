# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /home/lucas/installed/clion/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/lucas/installed/clion/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lucas/work/furg/distribuidos_sistemas/trabalho1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lucas/work/furg/distribuidos_sistemas/trabalho1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/flags.make

CMakeFiles/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/loader.cpp.o: CMakeFiles/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/flags.make
CMakeFiles/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/loader.cpp.o: ../loader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lucas/work/furg/distribuidos_sistemas/trabalho1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles//home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/loader.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles//home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/loader.cpp.o -c /home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.cpp

CMakeFiles/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/loader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles//home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/loader.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.cpp > CMakeFiles//home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/loader.cpp.i

CMakeFiles/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/loader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles//home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/loader.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.cpp -o CMakeFiles//home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/loader.cpp.s

CMakeFiles/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/loader.cpp.o.requires:

.PHONY : CMakeFiles/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/loader.cpp.o.requires

CMakeFiles/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/loader.cpp.o.provides: CMakeFiles/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/loader.cpp.o.requires
	$(MAKE) -f CMakeFiles//home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/build.make CMakeFiles//home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/loader.cpp.o.provides.build
.PHONY : CMakeFiles/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/loader.cpp.o.provides

CMakeFiles/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/loader.cpp.o.provides.build: CMakeFiles/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/loader.cpp.o


# Object files for target /home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader
/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader_OBJECTS = \
"CMakeFiles/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/loader.cpp.o"

# External object files for target /home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader
/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader_EXTERNAL_OBJECTS =

/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader: CMakeFiles/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/loader.cpp.o
/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader: CMakeFiles/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/build.make
/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader: CMakeFiles/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lucas/work/furg/distribuidos_sistemas/trabalho1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles//home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/build: /home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader

.PHONY : CMakeFiles/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/build

CMakeFiles/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/requires: CMakeFiles/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/loader.cpp.o.requires

.PHONY : CMakeFiles/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/requires

CMakeFiles/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles//home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/cmake_clean.cmake
.PHONY : CMakeFiles/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/clean

CMakeFiles/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/depend:
	cd /home/lucas/work/furg/distribuidos_sistemas/trabalho1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lucas/work/furg/distribuidos_sistemas/trabalho1 /home/lucas/work/furg/distribuidos_sistemas/trabalho1 /home/lucas/work/furg/distribuidos_sistemas/trabalho1/cmake-build-debug /home/lucas/work/furg/distribuidos_sistemas/trabalho1/cmake-build-debug /home/lucas/work/furg/distribuidos_sistemas/trabalho1/cmake-build-debug/CMakeFiles/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.dir/depend

