# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Study\IDE\Clion\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Study\IDE\Clion\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Study\GradeFour\CollegeFourLeaningNotes\Algorithm\Binary-Tree\Binary-Tree-Codes\Binary-Tree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Study\GradeFour\CollegeFourLeaningNotes\Algorithm\Binary-Tree\Binary-Tree-Codes\Binary-Tree\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Binary_Tree.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/Binary_Tree.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Binary_Tree.dir/flags.make

CMakeFiles/Binary_Tree.dir/main.cpp.obj: CMakeFiles/Binary_Tree.dir/flags.make
CMakeFiles/Binary_Tree.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Study\GradeFour\CollegeFourLeaningNotes\Algorithm\Binary-Tree\Binary-Tree-Codes\Binary-Tree\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Binary_Tree.dir/main.cpp.obj"
	D:\Environment\C++\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Binary_Tree.dir\main.cpp.obj -c D:\Study\GradeFour\CollegeFourLeaningNotes\Algorithm\Binary-Tree\Binary-Tree-Codes\Binary-Tree\main.cpp

CMakeFiles/Binary_Tree.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Binary_Tree.dir/main.cpp.i"
	D:\Environment\C++\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Study\GradeFour\CollegeFourLeaningNotes\Algorithm\Binary-Tree\Binary-Tree-Codes\Binary-Tree\main.cpp > CMakeFiles\Binary_Tree.dir\main.cpp.i

CMakeFiles/Binary_Tree.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Binary_Tree.dir/main.cpp.s"
	D:\Environment\C++\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Study\GradeFour\CollegeFourLeaningNotes\Algorithm\Binary-Tree\Binary-Tree-Codes\Binary-Tree\main.cpp -o CMakeFiles\Binary_Tree.dir\main.cpp.s

# Object files for target Binary_Tree
Binary_Tree_OBJECTS = \
"CMakeFiles/Binary_Tree.dir/main.cpp.obj"

# External object files for target Binary_Tree
Binary_Tree_EXTERNAL_OBJECTS =

Binary_Tree.exe: CMakeFiles/Binary_Tree.dir/main.cpp.obj
Binary_Tree.exe: CMakeFiles/Binary_Tree.dir/build.make
Binary_Tree.exe: CMakeFiles/Binary_Tree.dir/linklibs.rsp
Binary_Tree.exe: CMakeFiles/Binary_Tree.dir/objects1.rsp
Binary_Tree.exe: CMakeFiles/Binary_Tree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Study\GradeFour\CollegeFourLeaningNotes\Algorithm\Binary-Tree\Binary-Tree-Codes\Binary-Tree\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Binary_Tree.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Binary_Tree.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Binary_Tree.dir/build: Binary_Tree.exe
.PHONY : CMakeFiles/Binary_Tree.dir/build

CMakeFiles/Binary_Tree.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Binary_Tree.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Binary_Tree.dir/clean

CMakeFiles/Binary_Tree.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Study\GradeFour\CollegeFourLeaningNotes\Algorithm\Binary-Tree\Binary-Tree-Codes\Binary-Tree D:\Study\GradeFour\CollegeFourLeaningNotes\Algorithm\Binary-Tree\Binary-Tree-Codes\Binary-Tree D:\Study\GradeFour\CollegeFourLeaningNotes\Algorithm\Binary-Tree\Binary-Tree-Codes\Binary-Tree\cmake-build-debug D:\Study\GradeFour\CollegeFourLeaningNotes\Algorithm\Binary-Tree\Binary-Tree-Codes\Binary-Tree\cmake-build-debug D:\Study\GradeFour\CollegeFourLeaningNotes\Algorithm\Binary-Tree\Binary-Tree-Codes\Binary-Tree\cmake-build-debug\CMakeFiles\Binary_Tree.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Binary_Tree.dir/depend

