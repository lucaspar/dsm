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
include CMakeFiles/lmcomp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lmcomp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lmcomp.dir/flags.make

CMakeFiles/lmcomp.dir/loader.cpp.o: CMakeFiles/lmcomp.dir/flags.make
CMakeFiles/lmcomp.dir/loader.cpp.o: ../loader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lucas/work/furg/distribuidos_sistemas/trabalho1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lmcomp.dir/loader.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lmcomp.dir/loader.cpp.o -c /home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.cpp

CMakeFiles/lmcomp.dir/loader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lmcomp.dir/loader.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.cpp > CMakeFiles/lmcomp.dir/loader.cpp.i

CMakeFiles/lmcomp.dir/loader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lmcomp.dir/loader.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lucas/work/furg/distribuidos_sistemas/trabalho1/loader.cpp -o CMakeFiles/lmcomp.dir/loader.cpp.s

CMakeFiles/lmcomp.dir/loader.cpp.o.requires:

.PHONY : CMakeFiles/lmcomp.dir/loader.cpp.o.requires

CMakeFiles/lmcomp.dir/loader.cpp.o.provides: CMakeFiles/lmcomp.dir/loader.cpp.o.requires
	$(MAKE) -f CMakeFiles/lmcomp.dir/build.make CMakeFiles/lmcomp.dir/loader.cpp.o.provides.build
.PHONY : CMakeFiles/lmcomp.dir/loader.cpp.o.provides

CMakeFiles/lmcomp.dir/loader.cpp.o.provides.build: CMakeFiles/lmcomp.dir/loader.cpp.o


CMakeFiles/lmcomp.dir/sma.cpp.o: CMakeFiles/lmcomp.dir/flags.make
CMakeFiles/lmcomp.dir/sma.cpp.o: ../sma.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lucas/work/furg/distribuidos_sistemas/trabalho1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/lmcomp.dir/sma.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lmcomp.dir/sma.cpp.o -c /home/lucas/work/furg/distribuidos_sistemas/trabalho1/sma.cpp

CMakeFiles/lmcomp.dir/sma.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lmcomp.dir/sma.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lucas/work/furg/distribuidos_sistemas/trabalho1/sma.cpp > CMakeFiles/lmcomp.dir/sma.cpp.i

CMakeFiles/lmcomp.dir/sma.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lmcomp.dir/sma.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lucas/work/furg/distribuidos_sistemas/trabalho1/sma.cpp -o CMakeFiles/lmcomp.dir/sma.cpp.s

CMakeFiles/lmcomp.dir/sma.cpp.o.requires:

.PHONY : CMakeFiles/lmcomp.dir/sma.cpp.o.requires

CMakeFiles/lmcomp.dir/sma.cpp.o.provides: CMakeFiles/lmcomp.dir/sma.cpp.o.requires
	$(MAKE) -f CMakeFiles/lmcomp.dir/build.make CMakeFiles/lmcomp.dir/sma.cpp.o.provides.build
.PHONY : CMakeFiles/lmcomp.dir/sma.cpp.o.provides

CMakeFiles/lmcomp.dir/sma.cpp.o.provides.build: CMakeFiles/lmcomp.dir/sma.cpp.o


# Object files for target lmcomp
lmcomp_OBJECTS = \
"CMakeFiles/lmcomp.dir/loader.cpp.o" \
"CMakeFiles/lmcomp.dir/sma.cpp.o"

# External object files for target lmcomp
lmcomp_EXTERNAL_OBJECTS =

liblmcomp.a: CMakeFiles/lmcomp.dir/loader.cpp.o
liblmcomp.a: CMakeFiles/lmcomp.dir/sma.cpp.o
liblmcomp.a: CMakeFiles/lmcomp.dir/build.make
liblmcomp.a: CMakeFiles/lmcomp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lucas/work/furg/distribuidos_sistemas/trabalho1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library liblmcomp.a"
	$(CMAKE_COMMAND) -P CMakeFiles/lmcomp.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lmcomp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lmcomp.dir/build: liblmcomp.a

.PHONY : CMakeFiles/lmcomp.dir/build

CMakeFiles/lmcomp.dir/requires: CMakeFiles/lmcomp.dir/loader.cpp.o.requires
CMakeFiles/lmcomp.dir/requires: CMakeFiles/lmcomp.dir/sma.cpp.o.requires

.PHONY : CMakeFiles/lmcomp.dir/requires

CMakeFiles/lmcomp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lmcomp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lmcomp.dir/clean

CMakeFiles/lmcomp.dir/depend:
	cd /home/lucas/work/furg/distribuidos_sistemas/trabalho1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lucas/work/furg/distribuidos_sistemas/trabalho1 /home/lucas/work/furg/distribuidos_sistemas/trabalho1 /home/lucas/work/furg/distribuidos_sistemas/trabalho1/cmake-build-debug /home/lucas/work/furg/distribuidos_sistemas/trabalho1/cmake-build-debug /home/lucas/work/furg/distribuidos_sistemas/trabalho1/cmake-build-debug/CMakeFiles/lmcomp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lmcomp.dir/depend

