# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/n545n545/Code-Challenge-10-9-18/MemoryPool

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/n545n545/Code-Challenge-10-9-18/MemoryPool

# Include any dependencies generated for this target.
include CMakeFiles/tests.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tests.dir/flags.make

CMakeFiles/tests.dir/test-memory-pool.c.o: CMakeFiles/tests.dir/flags.make
CMakeFiles/tests.dir/test-memory-pool.c.o: test-memory-pool.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/n545n545/Code-Challenge-10-9-18/MemoryPool/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/tests.dir/test-memory-pool.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tests.dir/test-memory-pool.c.o   -c /home/n545n545/Code-Challenge-10-9-18/MemoryPool/test-memory-pool.c

CMakeFiles/tests.dir/test-memory-pool.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tests.dir/test-memory-pool.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/n545n545/Code-Challenge-10-9-18/MemoryPool/test-memory-pool.c > CMakeFiles/tests.dir/test-memory-pool.c.i

CMakeFiles/tests.dir/test-memory-pool.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tests.dir/test-memory-pool.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/n545n545/Code-Challenge-10-9-18/MemoryPool/test-memory-pool.c -o CMakeFiles/tests.dir/test-memory-pool.c.s

CMakeFiles/tests.dir/test-memory-pool.c.o.requires:

.PHONY : CMakeFiles/tests.dir/test-memory-pool.c.o.requires

CMakeFiles/tests.dir/test-memory-pool.c.o.provides: CMakeFiles/tests.dir/test-memory-pool.c.o.requires
	$(MAKE) -f CMakeFiles/tests.dir/build.make CMakeFiles/tests.dir/test-memory-pool.c.o.provides.build
.PHONY : CMakeFiles/tests.dir/test-memory-pool.c.o.provides

CMakeFiles/tests.dir/test-memory-pool.c.o.provides.build: CMakeFiles/tests.dir/test-memory-pool.c.o


CMakeFiles/tests.dir/memory_pool.c.o: CMakeFiles/tests.dir/flags.make
CMakeFiles/tests.dir/memory_pool.c.o: memory_pool.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/n545n545/Code-Challenge-10-9-18/MemoryPool/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/tests.dir/memory_pool.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tests.dir/memory_pool.c.o   -c /home/n545n545/Code-Challenge-10-9-18/MemoryPool/memory_pool.c

CMakeFiles/tests.dir/memory_pool.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tests.dir/memory_pool.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/n545n545/Code-Challenge-10-9-18/MemoryPool/memory_pool.c > CMakeFiles/tests.dir/memory_pool.c.i

CMakeFiles/tests.dir/memory_pool.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tests.dir/memory_pool.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/n545n545/Code-Challenge-10-9-18/MemoryPool/memory_pool.c -o CMakeFiles/tests.dir/memory_pool.c.s

CMakeFiles/tests.dir/memory_pool.c.o.requires:

.PHONY : CMakeFiles/tests.dir/memory_pool.c.o.requires

CMakeFiles/tests.dir/memory_pool.c.o.provides: CMakeFiles/tests.dir/memory_pool.c.o.requires
	$(MAKE) -f CMakeFiles/tests.dir/build.make CMakeFiles/tests.dir/memory_pool.c.o.provides.build
.PHONY : CMakeFiles/tests.dir/memory_pool.c.o.provides

CMakeFiles/tests.dir/memory_pool.c.o.provides.build: CMakeFiles/tests.dir/memory_pool.c.o


# Object files for target tests
tests_OBJECTS = \
"CMakeFiles/tests.dir/test-memory-pool.c.o" \
"CMakeFiles/tests.dir/memory_pool.c.o"

# External object files for target tests
tests_EXTERNAL_OBJECTS =

tests: CMakeFiles/tests.dir/test-memory-pool.c.o
tests: CMakeFiles/tests.dir/memory_pool.c.o
tests: CMakeFiles/tests.dir/build.make
tests: CMakeFiles/tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/n545n545/Code-Challenge-10-9-18/MemoryPool/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable tests"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tests.dir/build: tests

.PHONY : CMakeFiles/tests.dir/build

CMakeFiles/tests.dir/requires: CMakeFiles/tests.dir/test-memory-pool.c.o.requires
CMakeFiles/tests.dir/requires: CMakeFiles/tests.dir/memory_pool.c.o.requires

.PHONY : CMakeFiles/tests.dir/requires

CMakeFiles/tests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tests.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tests.dir/clean

CMakeFiles/tests.dir/depend:
	cd /home/n545n545/Code-Challenge-10-9-18/MemoryPool && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/n545n545/Code-Challenge-10-9-18/MemoryPool /home/n545n545/Code-Challenge-10-9-18/MemoryPool /home/n545n545/Code-Challenge-10-9-18/MemoryPool /home/n545n545/Code-Challenge-10-9-18/MemoryPool /home/n545n545/Code-Challenge-10-9-18/MemoryPool/CMakeFiles/tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tests.dir/depend
