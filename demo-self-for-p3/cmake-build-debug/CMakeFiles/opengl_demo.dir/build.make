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
CMAKE_COMMAND = "/Users/Tommy/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/193.6911.21/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/Tommy/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/193.6911.21/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/opengl_demo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/opengl_demo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/opengl_demo.dir/flags.make

CMakeFiles/opengl_demo.dir/src/Camera.cpp.o: CMakeFiles/opengl_demo.dir/flags.make
CMakeFiles/opengl_demo.dir/src/Camera.cpp.o: ../src/Camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/opengl_demo.dir/src/Camera.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/opengl_demo.dir/src/Camera.cpp.o -c /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/Camera.cpp

CMakeFiles/opengl_demo.dir/src/Camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opengl_demo.dir/src/Camera.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/Camera.cpp > CMakeFiles/opengl_demo.dir/src/Camera.cpp.i

CMakeFiles/opengl_demo.dir/src/Camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opengl_demo.dir/src/Camera.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/Camera.cpp -o CMakeFiles/opengl_demo.dir/src/Camera.cpp.s

CMakeFiles/opengl_demo.dir/src/LightDirectional.cpp.o: CMakeFiles/opengl_demo.dir/flags.make
CMakeFiles/opengl_demo.dir/src/LightDirectional.cpp.o: ../src/LightDirectional.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/opengl_demo.dir/src/LightDirectional.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/opengl_demo.dir/src/LightDirectional.cpp.o -c /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/LightDirectional.cpp

CMakeFiles/opengl_demo.dir/src/LightDirectional.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opengl_demo.dir/src/LightDirectional.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/LightDirectional.cpp > CMakeFiles/opengl_demo.dir/src/LightDirectional.cpp.i

CMakeFiles/opengl_demo.dir/src/LightDirectional.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opengl_demo.dir/src/LightDirectional.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/LightDirectional.cpp -o CMakeFiles/opengl_demo.dir/src/LightDirectional.cpp.s

CMakeFiles/opengl_demo.dir/src/LightPoint.cpp.o: CMakeFiles/opengl_demo.dir/flags.make
CMakeFiles/opengl_demo.dir/src/LightPoint.cpp.o: ../src/LightPoint.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/opengl_demo.dir/src/LightPoint.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/opengl_demo.dir/src/LightPoint.cpp.o -c /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/LightPoint.cpp

CMakeFiles/opengl_demo.dir/src/LightPoint.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opengl_demo.dir/src/LightPoint.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/LightPoint.cpp > CMakeFiles/opengl_demo.dir/src/LightPoint.cpp.i

CMakeFiles/opengl_demo.dir/src/LightPoint.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opengl_demo.dir/src/LightPoint.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/LightPoint.cpp -o CMakeFiles/opengl_demo.dir/src/LightPoint.cpp.s

CMakeFiles/opengl_demo.dir/src/LightSpot.cpp.o: CMakeFiles/opengl_demo.dir/flags.make
CMakeFiles/opengl_demo.dir/src/LightSpot.cpp.o: ../src/LightSpot.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/opengl_demo.dir/src/LightSpot.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/opengl_demo.dir/src/LightSpot.cpp.o -c /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/LightSpot.cpp

CMakeFiles/opengl_demo.dir/src/LightSpot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opengl_demo.dir/src/LightSpot.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/LightSpot.cpp > CMakeFiles/opengl_demo.dir/src/LightSpot.cpp.i

CMakeFiles/opengl_demo.dir/src/LightSpot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opengl_demo.dir/src/LightSpot.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/LightSpot.cpp -o CMakeFiles/opengl_demo.dir/src/LightSpot.cpp.s

CMakeFiles/opengl_demo.dir/src/Mesh.cpp.o: CMakeFiles/opengl_demo.dir/flags.make
CMakeFiles/opengl_demo.dir/src/Mesh.cpp.o: ../src/Mesh.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/opengl_demo.dir/src/Mesh.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/opengl_demo.dir/src/Mesh.cpp.o -c /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/Mesh.cpp

CMakeFiles/opengl_demo.dir/src/Mesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opengl_demo.dir/src/Mesh.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/Mesh.cpp > CMakeFiles/opengl_demo.dir/src/Mesh.cpp.i

CMakeFiles/opengl_demo.dir/src/Mesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opengl_demo.dir/src/Mesh.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/Mesh.cpp -o CMakeFiles/opengl_demo.dir/src/Mesh.cpp.s

CMakeFiles/opengl_demo.dir/src/Model.cpp.o: CMakeFiles/opengl_demo.dir/flags.make
CMakeFiles/opengl_demo.dir/src/Model.cpp.o: ../src/Model.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/opengl_demo.dir/src/Model.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/opengl_demo.dir/src/Model.cpp.o -c /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/Model.cpp

CMakeFiles/opengl_demo.dir/src/Model.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opengl_demo.dir/src/Model.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/Model.cpp > CMakeFiles/opengl_demo.dir/src/Model.cpp.i

CMakeFiles/opengl_demo.dir/src/Model.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opengl_demo.dir/src/Model.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/Model.cpp -o CMakeFiles/opengl_demo.dir/src/Model.cpp.s

CMakeFiles/opengl_demo.dir/src/Shade.cpp.o: CMakeFiles/opengl_demo.dir/flags.make
CMakeFiles/opengl_demo.dir/src/Shade.cpp.o: ../src/Shade.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/opengl_demo.dir/src/Shade.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/opengl_demo.dir/src/Shade.cpp.o -c /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/Shade.cpp

CMakeFiles/opengl_demo.dir/src/Shade.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opengl_demo.dir/src/Shade.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/Shade.cpp > CMakeFiles/opengl_demo.dir/src/Shade.cpp.i

CMakeFiles/opengl_demo.dir/src/Shade.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opengl_demo.dir/src/Shade.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/Shade.cpp -o CMakeFiles/opengl_demo.dir/src/Shade.cpp.s

CMakeFiles/opengl_demo.dir/src/geometry.cpp.o: CMakeFiles/opengl_demo.dir/flags.make
CMakeFiles/opengl_demo.dir/src/geometry.cpp.o: ../src/geometry.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/opengl_demo.dir/src/geometry.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/opengl_demo.dir/src/geometry.cpp.o -c /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/geometry.cpp

CMakeFiles/opengl_demo.dir/src/geometry.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opengl_demo.dir/src/geometry.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/geometry.cpp > CMakeFiles/opengl_demo.dir/src/geometry.cpp.i

CMakeFiles/opengl_demo.dir/src/geometry.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opengl_demo.dir/src/geometry.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/geometry.cpp -o CMakeFiles/opengl_demo.dir/src/geometry.cpp.s

CMakeFiles/opengl_demo.dir/src/image.cpp.o: CMakeFiles/opengl_demo.dir/flags.make
CMakeFiles/opengl_demo.dir/src/image.cpp.o: ../src/image.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/opengl_demo.dir/src/image.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/opengl_demo.dir/src/image.cpp.o -c /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/image.cpp

CMakeFiles/opengl_demo.dir/src/image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opengl_demo.dir/src/image.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/image.cpp > CMakeFiles/opengl_demo.dir/src/image.cpp.i

CMakeFiles/opengl_demo.dir/src/image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opengl_demo.dir/src/image.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/image.cpp -o CMakeFiles/opengl_demo.dir/src/image.cpp.s

CMakeFiles/opengl_demo.dir/src/main.cpp.o: CMakeFiles/opengl_demo.dir/flags.make
CMakeFiles/opengl_demo.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/opengl_demo.dir/src/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/opengl_demo.dir/src/main.cpp.o -c /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/main.cpp

CMakeFiles/opengl_demo.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opengl_demo.dir/src/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/main.cpp > CMakeFiles/opengl_demo.dir/src/main.cpp.i

CMakeFiles/opengl_demo.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opengl_demo.dir/src/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/main.cpp -o CMakeFiles/opengl_demo.dir/src/main.cpp.s

CMakeFiles/opengl_demo.dir/src/shader.cpp.o: CMakeFiles/opengl_demo.dir/flags.make
CMakeFiles/opengl_demo.dir/src/shader.cpp.o: ../src/shader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/opengl_demo.dir/src/shader.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/opengl_demo.dir/src/shader.cpp.o -c /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/shader.cpp

CMakeFiles/opengl_demo.dir/src/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opengl_demo.dir/src/shader.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/shader.cpp > CMakeFiles/opengl_demo.dir/src/shader.cpp.i

CMakeFiles/opengl_demo.dir/src/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opengl_demo.dir/src/shader.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/shader.cpp -o CMakeFiles/opengl_demo.dir/src/shader.cpp.s

CMakeFiles/opengl_demo.dir/src/utils.cpp.o: CMakeFiles/opengl_demo.dir/flags.make
CMakeFiles/opengl_demo.dir/src/utils.cpp.o: ../src/utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/opengl_demo.dir/src/utils.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/opengl_demo.dir/src/utils.cpp.o -c /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/utils.cpp

CMakeFiles/opengl_demo.dir/src/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opengl_demo.dir/src/utils.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/utils.cpp > CMakeFiles/opengl_demo.dir/src/utils.cpp.i

CMakeFiles/opengl_demo.dir/src/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opengl_demo.dir/src/utils.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/src/utils.cpp -o CMakeFiles/opengl_demo.dir/src/utils.cpp.s

# Object files for target opengl_demo
opengl_demo_OBJECTS = \
"CMakeFiles/opengl_demo.dir/src/Camera.cpp.o" \
"CMakeFiles/opengl_demo.dir/src/LightDirectional.cpp.o" \
"CMakeFiles/opengl_demo.dir/src/LightPoint.cpp.o" \
"CMakeFiles/opengl_demo.dir/src/LightSpot.cpp.o" \
"CMakeFiles/opengl_demo.dir/src/Mesh.cpp.o" \
"CMakeFiles/opengl_demo.dir/src/Model.cpp.o" \
"CMakeFiles/opengl_demo.dir/src/Shade.cpp.o" \
"CMakeFiles/opengl_demo.dir/src/geometry.cpp.o" \
"CMakeFiles/opengl_demo.dir/src/image.cpp.o" \
"CMakeFiles/opengl_demo.dir/src/main.cpp.o" \
"CMakeFiles/opengl_demo.dir/src/shader.cpp.o" \
"CMakeFiles/opengl_demo.dir/src/utils.cpp.o"

# External object files for target opengl_demo
opengl_demo_EXTERNAL_OBJECTS =

opengl_demo_Debug/opengl_demo: CMakeFiles/opengl_demo.dir/src/Camera.cpp.o
opengl_demo_Debug/opengl_demo: CMakeFiles/opengl_demo.dir/src/LightDirectional.cpp.o
opengl_demo_Debug/opengl_demo: CMakeFiles/opengl_demo.dir/src/LightPoint.cpp.o
opengl_demo_Debug/opengl_demo: CMakeFiles/opengl_demo.dir/src/LightSpot.cpp.o
opengl_demo_Debug/opengl_demo: CMakeFiles/opengl_demo.dir/src/Mesh.cpp.o
opengl_demo_Debug/opengl_demo: CMakeFiles/opengl_demo.dir/src/Model.cpp.o
opengl_demo_Debug/opengl_demo: CMakeFiles/opengl_demo.dir/src/Shade.cpp.o
opengl_demo_Debug/opengl_demo: CMakeFiles/opengl_demo.dir/src/geometry.cpp.o
opengl_demo_Debug/opengl_demo: CMakeFiles/opengl_demo.dir/src/image.cpp.o
opengl_demo_Debug/opengl_demo: CMakeFiles/opengl_demo.dir/src/main.cpp.o
opengl_demo_Debug/opengl_demo: CMakeFiles/opengl_demo.dir/src/shader.cpp.o
opengl_demo_Debug/opengl_demo: CMakeFiles/opengl_demo.dir/src/utils.cpp.o
opengl_demo_Debug/opengl_demo: CMakeFiles/opengl_demo.dir/build.make
opengl_demo_Debug/opengl_demo: /usr/local/Cellar/glfw/3.3/lib/libglfw.3.dylib
opengl_demo_Debug/opengl_demo: external/assimp/code/libassimpd.4.1.0.dylib
opengl_demo_Debug/opengl_demo: /usr/lib/libz.dylib
opengl_demo_Debug/opengl_demo: external/assimp/contrib/irrXML/libIrrXMLd.a
opengl_demo_Debug/opengl_demo: /usr/local/Cellar/glfw/3.3/lib/libglfw.3.dylib
opengl_demo_Debug/opengl_demo: CMakeFiles/opengl_demo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX executable opengl_demo_Debug/opengl_demo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/opengl_demo.dir/link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Creating symlink to shader directory"
	"/Users/Tommy/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/193.6911.21/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E create_symlink /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/shader /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/cmake-build-debug/opengl_demo_Debug/shader
	"/Users/Tommy/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/193.6911.21/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E copy_directory /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/images /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/cmake-build-debug/opengl_demo_Debug/images

# Rule to build all files generated by this target.
CMakeFiles/opengl_demo.dir/build: opengl_demo_Debug/opengl_demo

.PHONY : CMakeFiles/opengl_demo.dir/build

CMakeFiles/opengl_demo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/opengl_demo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/opengl_demo.dir/clean

CMakeFiles/opengl_demo.dir/depend:
	cd /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3 /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3 /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/cmake-build-debug /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/cmake-build-debug /Users/Tommy/Desktop/studyInMassey/159_709ComputerGraphics/demo-self-for-p3/cmake-build-debug/CMakeFiles/opengl_demo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/opengl_demo.dir/depend

