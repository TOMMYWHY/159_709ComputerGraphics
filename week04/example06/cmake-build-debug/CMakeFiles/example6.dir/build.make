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
CMAKE_SOURCE_DIR = /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week04/example06

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week04/example06/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/example6.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/example6.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/example6.dir/flags.make

CMakeFiles/example6.dir/src/example06.cpp.o: CMakeFiles/example6.dir/flags.make
CMakeFiles/example6.dir/src/example06.cpp.o: ../src/example06.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week04/example06/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/example6.dir/src/example06.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example6.dir/src/example06.cpp.o -c /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week04/example06/src/example06.cpp

CMakeFiles/example6.dir/src/example06.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example6.dir/src/example06.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week04/example06/src/example06.cpp > CMakeFiles/example6.dir/src/example06.cpp.i

CMakeFiles/example6.dir/src/example06.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example6.dir/src/example06.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week04/example06/src/example06.cpp -o CMakeFiles/example6.dir/src/example06.cpp.s

CMakeFiles/example6.dir/src/geometry.cpp.o: CMakeFiles/example6.dir/flags.make
CMakeFiles/example6.dir/src/geometry.cpp.o: ../src/geometry.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week04/example06/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/example6.dir/src/geometry.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example6.dir/src/geometry.cpp.o -c /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week04/example06/src/geometry.cpp

CMakeFiles/example6.dir/src/geometry.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example6.dir/src/geometry.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week04/example06/src/geometry.cpp > CMakeFiles/example6.dir/src/geometry.cpp.i

CMakeFiles/example6.dir/src/geometry.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example6.dir/src/geometry.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week04/example06/src/geometry.cpp -o CMakeFiles/example6.dir/src/geometry.cpp.s

CMakeFiles/example6.dir/src/shader.cpp.o: CMakeFiles/example6.dir/flags.make
CMakeFiles/example6.dir/src/shader.cpp.o: ../src/shader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week04/example06/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/example6.dir/src/shader.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example6.dir/src/shader.cpp.o -c /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week04/example06/src/shader.cpp

CMakeFiles/example6.dir/src/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example6.dir/src/shader.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week04/example06/src/shader.cpp > CMakeFiles/example6.dir/src/shader.cpp.i

CMakeFiles/example6.dir/src/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example6.dir/src/shader.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week04/example06/src/shader.cpp -o CMakeFiles/example6.dir/src/shader.cpp.s

CMakeFiles/example6.dir/src/utils.cpp.o: CMakeFiles/example6.dir/flags.make
CMakeFiles/example6.dir/src/utils.cpp.o: ../src/utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week04/example06/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/example6.dir/src/utils.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example6.dir/src/utils.cpp.o -c /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week04/example06/src/utils.cpp

CMakeFiles/example6.dir/src/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example6.dir/src/utils.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week04/example06/src/utils.cpp > CMakeFiles/example6.dir/src/utils.cpp.i

CMakeFiles/example6.dir/src/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example6.dir/src/utils.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week04/example06/src/utils.cpp -o CMakeFiles/example6.dir/src/utils.cpp.s

# Object files for target example6
example6_OBJECTS = \
"CMakeFiles/example6.dir/src/example06.cpp.o" \
"CMakeFiles/example6.dir/src/geometry.cpp.o" \
"CMakeFiles/example6.dir/src/shader.cpp.o" \
"CMakeFiles/example6.dir/src/utils.cpp.o"

# External object files for target example6
example6_EXTERNAL_OBJECTS =

example6_Debug/example6: CMakeFiles/example6.dir/src/example06.cpp.o
example6_Debug/example6: CMakeFiles/example6.dir/src/geometry.cpp.o
example6_Debug/example6: CMakeFiles/example6.dir/src/shader.cpp.o
example6_Debug/example6: CMakeFiles/example6.dir/src/utils.cpp.o
example6_Debug/example6: CMakeFiles/example6.dir/build.make
example6_Debug/example6: /usr/local/Cellar/glfw/3.3/lib/libglfw.3.dylib
example6_Debug/example6: CMakeFiles/example6.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week04/example06/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable example6_Debug/example6"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/example6.dir/link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Creating symlink to shader directory"
	"/Users/Tommy/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/192.5728.100/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E create_symlink /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week04/example06/shaders /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week04/example06/cmake-build-debug/example6_Debug/shaders

# Rule to build all files generated by this target.
CMakeFiles/example6.dir/build: example6_Debug/example6

.PHONY : CMakeFiles/example6.dir/build

CMakeFiles/example6.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/example6.dir/cmake_clean.cmake
.PHONY : CMakeFiles/example6.dir/clean

CMakeFiles/example6.dir/depend:
	cd /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week04/example06/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week04/example06 /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week04/example06 /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week04/example06/cmake-build-debug /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week04/example06/cmake-build-debug /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/week04/example06/cmake-build-debug/CMakeFiles/example6.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/example6.dir/depend
