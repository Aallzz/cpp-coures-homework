# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = "/home/alexander/study/main/programming/C++/programs /persistent_set/persistent_set"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/alexander/study/main/programming/C++/programs /persistent_set/build-persistent_set-Desktop_Qt_5_9_1_GCC_64bit-Default"

# Include any dependencies generated for this target.
include CMakeFiles/persistent_set.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/persistent_set.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/persistent_set.dir/flags.make

CMakeFiles/persistent_set.dir/main.cpp.o: CMakeFiles/persistent_set.dir/flags.make
CMakeFiles/persistent_set.dir/main.cpp.o: /home/alexander/study/main/programming/C++/programs\ /persistent_set/persistent_set/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/alexander/study/main/programming/C++/programs /persistent_set/build-persistent_set-Desktop_Qt_5_9_1_GCC_64bit-Default/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/persistent_set.dir/main.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/persistent_set.dir/main.cpp.o -c "/home/alexander/study/main/programming/C++/programs /persistent_set/persistent_set/main.cpp"

CMakeFiles/persistent_set.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/persistent_set.dir/main.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/alexander/study/main/programming/C++/programs /persistent_set/persistent_set/main.cpp" > CMakeFiles/persistent_set.dir/main.cpp.i

CMakeFiles/persistent_set.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/persistent_set.dir/main.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/alexander/study/main/programming/C++/programs /persistent_set/persistent_set/main.cpp" -o CMakeFiles/persistent_set.dir/main.cpp.s

CMakeFiles/persistent_set.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/persistent_set.dir/main.cpp.o.requires

CMakeFiles/persistent_set.dir/main.cpp.o.provides: CMakeFiles/persistent_set.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/persistent_set.dir/build.make CMakeFiles/persistent_set.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/persistent_set.dir/main.cpp.o.provides

CMakeFiles/persistent_set.dir/main.cpp.o.provides.build: CMakeFiles/persistent_set.dir/main.cpp.o


# Object files for target persistent_set
persistent_set_OBJECTS = \
"CMakeFiles/persistent_set.dir/main.cpp.o"

# External object files for target persistent_set
persistent_set_EXTERNAL_OBJECTS =

persistent_set: CMakeFiles/persistent_set.dir/main.cpp.o
persistent_set: CMakeFiles/persistent_set.dir/build.make
persistent_set: CMakeFiles/persistent_set.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/alexander/study/main/programming/C++/programs /persistent_set/build-persistent_set-Desktop_Qt_5_9_1_GCC_64bit-Default/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable persistent_set"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/persistent_set.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/persistent_set.dir/build: persistent_set

.PHONY : CMakeFiles/persistent_set.dir/build

CMakeFiles/persistent_set.dir/requires: CMakeFiles/persistent_set.dir/main.cpp.o.requires

.PHONY : CMakeFiles/persistent_set.dir/requires

CMakeFiles/persistent_set.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/persistent_set.dir/cmake_clean.cmake
.PHONY : CMakeFiles/persistent_set.dir/clean

CMakeFiles/persistent_set.dir/depend:
	cd "/home/alexander/study/main/programming/C++/programs /persistent_set/build-persistent_set-Desktop_Qt_5_9_1_GCC_64bit-Default" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/alexander/study/main/programming/C++/programs /persistent_set/persistent_set" "/home/alexander/study/main/programming/C++/programs /persistent_set/persistent_set" "/home/alexander/study/main/programming/C++/programs /persistent_set/build-persistent_set-Desktop_Qt_5_9_1_GCC_64bit-Default" "/home/alexander/study/main/programming/C++/programs /persistent_set/build-persistent_set-Desktop_Qt_5_9_1_GCC_64bit-Default" "/home/alexander/study/main/programming/C++/programs /persistent_set/build-persistent_set-Desktop_Qt_5_9_1_GCC_64bit-Default/CMakeFiles/persistent_set.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/persistent_set.dir/depend
