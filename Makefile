# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_BINARY_DIR = /home/lucas/work/furg/distribuidos_sistemas/trabalho1

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/home/lucas/installed/clion/bin/cmake/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/home/lucas/installed/clion/bin/cmake/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/lucas/work/furg/distribuidos_sistemas/trabalho1/CMakeFiles /home/lucas/work/furg/distribuidos_sistemas/trabalho1/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/lucas/work/furg/distribuidos_sistemas/trabalho1/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named lmcomp

# Build rule for target.
lmcomp: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 lmcomp
.PHONY : lmcomp

# fast build rule for target.
lmcomp/fast:
	$(MAKE) -f CMakeFiles/lmcomp.dir/build.make CMakeFiles/lmcomp.dir/build
.PHONY : lmcomp/fast

#=============================================================================
# Target rules for targets named server

# Build rule for target.
server: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 server
.PHONY : server

# fast build rule for target.
server/fast:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/build
.PHONY : server/fast

#=============================================================================
# Target rules for targets named client

# Build rule for target.
client: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 client
.PHONY : client

# fast build rule for target.
client/fast:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/build
.PHONY : client/fast

SHMessage.o: SHMessage.cpp.o

.PHONY : SHMessage.o

# target to build an object file
SHMessage.cpp.o:
	$(MAKE) -f CMakeFiles/lmcomp.dir/build.make CMakeFiles/lmcomp.dir/SHMessage.cpp.o
.PHONY : SHMessage.cpp.o

SHMessage.i: SHMessage.cpp.i

.PHONY : SHMessage.i

# target to preprocess a source file
SHMessage.cpp.i:
	$(MAKE) -f CMakeFiles/lmcomp.dir/build.make CMakeFiles/lmcomp.dir/SHMessage.cpp.i
.PHONY : SHMessage.cpp.i

SHMessage.s: SHMessage.cpp.s

.PHONY : SHMessage.s

# target to generate assembly for a file
SHMessage.cpp.s:
	$(MAKE) -f CMakeFiles/lmcomp.dir/build.make CMakeFiles/lmcomp.dir/SHMessage.cpp.s
.PHONY : SHMessage.cpp.s

client.o: client.cpp.o

.PHONY : client.o

# target to build an object file
client.cpp.o:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/client.cpp.o
.PHONY : client.cpp.o

client.i: client.cpp.i

.PHONY : client.i

# target to preprocess a source file
client.cpp.i:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/client.cpp.i
.PHONY : client.cpp.i

client.s: client.cpp.s

.PHONY : client.s

# target to generate assembly for a file
client.cpp.s:
	$(MAKE) -f CMakeFiles/client.dir/build.make CMakeFiles/client.dir/client.cpp.s
.PHONY : client.cpp.s

loader.o: loader.cpp.o

.PHONY : loader.o

# target to build an object file
loader.cpp.o:
	$(MAKE) -f CMakeFiles/lmcomp.dir/build.make CMakeFiles/lmcomp.dir/loader.cpp.o
.PHONY : loader.cpp.o

loader.i: loader.cpp.i

.PHONY : loader.i

# target to preprocess a source file
loader.cpp.i:
	$(MAKE) -f CMakeFiles/lmcomp.dir/build.make CMakeFiles/lmcomp.dir/loader.cpp.i
.PHONY : loader.cpp.i

loader.s: loader.cpp.s

.PHONY : loader.s

# target to generate assembly for a file
loader.cpp.s:
	$(MAKE) -f CMakeFiles/lmcomp.dir/build.make CMakeFiles/lmcomp.dir/loader.cpp.s
.PHONY : loader.cpp.s

logger.o: logger.cpp.o

.PHONY : logger.o

# target to build an object file
logger.cpp.o:
	$(MAKE) -f CMakeFiles/lmcomp.dir/build.make CMakeFiles/lmcomp.dir/logger.cpp.o
.PHONY : logger.cpp.o

logger.i: logger.cpp.i

.PHONY : logger.i

# target to preprocess a source file
logger.cpp.i:
	$(MAKE) -f CMakeFiles/lmcomp.dir/build.make CMakeFiles/lmcomp.dir/logger.cpp.i
.PHONY : logger.cpp.i

logger.s: logger.cpp.s

.PHONY : logger.s

# target to generate assembly for a file
logger.cpp.s:
	$(MAKE) -f CMakeFiles/lmcomp.dir/build.make CMakeFiles/lmcomp.dir/logger.cpp.s
.PHONY : logger.cpp.s

server.o: server.cpp.o

.PHONY : server.o

# target to build an object file
server.cpp.o:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/server.cpp.o
.PHONY : server.cpp.o

server.i: server.cpp.i

.PHONY : server.i

# target to preprocess a source file
server.cpp.i:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/server.cpp.i
.PHONY : server.cpp.i

server.s: server.cpp.s

.PHONY : server.s

# target to generate assembly for a file
server.cpp.s:
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/server.cpp.s
.PHONY : server.cpp.s

sma.o: sma.cpp.o

.PHONY : sma.o

# target to build an object file
sma.cpp.o:
	$(MAKE) -f CMakeFiles/lmcomp.dir/build.make CMakeFiles/lmcomp.dir/sma.cpp.o
.PHONY : sma.cpp.o

sma.i: sma.cpp.i

.PHONY : sma.i

# target to preprocess a source file
sma.cpp.i:
	$(MAKE) -f CMakeFiles/lmcomp.dir/build.make CMakeFiles/lmcomp.dir/sma.cpp.i
.PHONY : sma.cpp.i

sma.s: sma.cpp.s

.PHONY : sma.s

# target to generate assembly for a file
sma.cpp.s:
	$(MAKE) -f CMakeFiles/lmcomp.dir/build.make CMakeFiles/lmcomp.dir/sma.cpp.s
.PHONY : sma.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... lmcomp"
	@echo "... server"
	@echo "... client"
	@echo "... SHMessage.o"
	@echo "... SHMessage.i"
	@echo "... SHMessage.s"
	@echo "... client.o"
	@echo "... client.i"
	@echo "... client.s"
	@echo "... loader.o"
	@echo "... loader.i"
	@echo "... loader.s"
	@echo "... logger.o"
	@echo "... logger.i"
	@echo "... logger.s"
	@echo "... server.o"
	@echo "... server.i"
	@echo "... server.s"
	@echo "... sma.o"
	@echo "... sma.i"
	@echo "... sma.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

