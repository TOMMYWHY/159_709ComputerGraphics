# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = "/Users/Tommy/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/192.5728.100/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/Tommy/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/192.5728.100/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week03/demo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week03/demo

# Include any dependencies generated for this target.
include CMakeFiles/demo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/demo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/demo.dir/flags.make

CMakeFiles/demo.dir/src/source6.cpp.o: CMakeFiles/demo.dir/flags.make
CMakeFiles/demo.dir/src/source6.cpp.o: src/source6.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week03/demo/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/demo.dir/src/source6.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/demo.dir/src/source6.cpp.o -c /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week03/demo/src/source6.cpp

CMakeFiles/demo.dir/src/source6.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo.dir/src/source6.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week03/demo/src/source6.cpp > CMakeFiles/demo.dir/src/source6.cpp.i

CMakeFiles/demo.dir/src/source6.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo.dir/src/source6.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week03/demo/src/source6.cpp -o CMakeFiles/demo.dir/src/source6.cpp.s

# Object files for target demo
demo_OBJECTS = \
"CMakeFiles/demo.dir/src/source6.cpp.o"

# External object files for target demo
demo_EXTERNAL_OBJECTS =

demo_Debug/demo: CMakeFiles/demo.dir/src/source6.cpp.o
demo_Debug/demo: CMakeFiles/demo.dir/build.make
demo_Debug/demo: /usr/local/Cellar/glfw/3.3/lib/libglfw.3.dylib
demo_Debug/demo: CMakeFiles/demo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week03/demo/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable demo_Debug/demo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/demo.dir/link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Creating symlink to shader directory"
	"/Users/Tommy/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/192.5728.100/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E create_symlink /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week03/demo/shaders /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week03/demo/demo_Debug/shaders

# Rule to build all files generated by this target.
CMakeFiles/demo.dir/build: demo_Debug/demo

.PHONY : CMakeFiles/demo.dir/build

CMakeFiles/demo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/demo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/demo.dir/clean

CMakeFiles/demo.dir/depend:
	cd /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week03/demo && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week03/demo /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week03/demo /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week03/demo /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week03/demo /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week03/demo/CMakeFiles/demo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/demo.dir/depend

