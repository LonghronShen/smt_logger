# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /opt/clion-2019.3.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2019.3.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zhangfei/workspace/smt_logger_new

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zhangfei/workspace/smt_logger_new/cmake-build-debug

# Include any dependencies generated for this target.
include testcase/CMakeFiles/testcase.dir/depend.make

# Include the progress variables for this target.
include testcase/CMakeFiles/testcase.dir/progress.make

# Include the compile flags for this target's objects.
include testcase/CMakeFiles/testcase.dir/flags.make

testcase/CMakeFiles/testcase.dir/testcase.cpp.o: testcase/CMakeFiles/testcase.dir/flags.make
testcase/CMakeFiles/testcase.dir/testcase.cpp.o: ../testcase/testcase.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhangfei/workspace/smt_logger_new/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object testcase/CMakeFiles/testcase.dir/testcase.cpp.o"
	cd /home/zhangfei/workspace/smt_logger_new/cmake-build-debug/testcase && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testcase.dir/testcase.cpp.o -c /home/zhangfei/workspace/smt_logger_new/testcase/testcase.cpp

testcase/CMakeFiles/testcase.dir/testcase.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testcase.dir/testcase.cpp.i"
	cd /home/zhangfei/workspace/smt_logger_new/cmake-build-debug/testcase && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhangfei/workspace/smt_logger_new/testcase/testcase.cpp > CMakeFiles/testcase.dir/testcase.cpp.i

testcase/CMakeFiles/testcase.dir/testcase.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testcase.dir/testcase.cpp.s"
	cd /home/zhangfei/workspace/smt_logger_new/cmake-build-debug/testcase && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhangfei/workspace/smt_logger_new/testcase/testcase.cpp -o CMakeFiles/testcase.dir/testcase.cpp.s

# Object files for target testcase
testcase_OBJECTS = \
"CMakeFiles/testcase.dir/testcase.cpp.o"

# External object files for target testcase
testcase_EXTERNAL_OBJECTS =

bin/testcase: testcase/CMakeFiles/testcase.dir/testcase.cpp.o
bin/testcase: testcase/CMakeFiles/testcase.dir/build.make
bin/testcase: lib/libsmt_loggerd.so
bin/testcase: testcase/CMakeFiles/testcase.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zhangfei/workspace/smt_logger_new/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/testcase"
	cd /home/zhangfei/workspace/smt_logger_new/cmake-build-debug/testcase && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testcase.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
testcase/CMakeFiles/testcase.dir/build: bin/testcase

.PHONY : testcase/CMakeFiles/testcase.dir/build

testcase/CMakeFiles/testcase.dir/clean:
	cd /home/zhangfei/workspace/smt_logger_new/cmake-build-debug/testcase && $(CMAKE_COMMAND) -P CMakeFiles/testcase.dir/cmake_clean.cmake
.PHONY : testcase/CMakeFiles/testcase.dir/clean

testcase/CMakeFiles/testcase.dir/depend:
	cd /home/zhangfei/workspace/smt_logger_new/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zhangfei/workspace/smt_logger_new /home/zhangfei/workspace/smt_logger_new/testcase /home/zhangfei/workspace/smt_logger_new/cmake-build-debug /home/zhangfei/workspace/smt_logger_new/cmake-build-debug/testcase /home/zhangfei/workspace/smt_logger_new/cmake-build-debug/testcase/CMakeFiles/testcase.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : testcase/CMakeFiles/testcase.dir/depend

