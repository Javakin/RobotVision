# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /home/jarvis/clion-2017.2.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/jarvis/clion-2017.2.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/jarvis/Desktop/RobotVision/Vision project1/VisionPic3"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/jarvis/Desktop/RobotVision/Vision project1/VisionPic3/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/VisionPic3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/VisionPic3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/VisionPic3.dir/flags.make

CMakeFiles/VisionPic3.dir/src/main.cpp.o: CMakeFiles/VisionPic3.dir/flags.make
CMakeFiles/VisionPic3.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/jarvis/Desktop/RobotVision/Vision project1/VisionPic3/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/VisionPic3.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/VisionPic3.dir/src/main.cpp.o -c "/home/jarvis/Desktop/RobotVision/Vision project1/VisionPic3/src/main.cpp"

CMakeFiles/VisionPic3.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VisionPic3.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/jarvis/Desktop/RobotVision/Vision project1/VisionPic3/src/main.cpp" > CMakeFiles/VisionPic3.dir/src/main.cpp.i

CMakeFiles/VisionPic3.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VisionPic3.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/jarvis/Desktop/RobotVision/Vision project1/VisionPic3/src/main.cpp" -o CMakeFiles/VisionPic3.dir/src/main.cpp.s

CMakeFiles/VisionPic3.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/VisionPic3.dir/src/main.cpp.o.requires

CMakeFiles/VisionPic3.dir/src/main.cpp.o.provides: CMakeFiles/VisionPic3.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/VisionPic3.dir/build.make CMakeFiles/VisionPic3.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/VisionPic3.dir/src/main.cpp.o.provides

CMakeFiles/VisionPic3.dir/src/main.cpp.o.provides.build: CMakeFiles/VisionPic3.dir/src/main.cpp.o


# Object files for target VisionPic3
VisionPic3_OBJECTS = \
"CMakeFiles/VisionPic3.dir/src/main.cpp.o"

# External object files for target VisionPic3
VisionPic3_EXTERNAL_OBJECTS =

VisionPic3: CMakeFiles/VisionPic3.dir/src/main.cpp.o
VisionPic3: CMakeFiles/VisionPic3.dir/build.make
VisionPic3: /usr/local/lib/libopencv_shape.so.3.2.0
VisionPic3: /usr/local/lib/libopencv_stitching.so.3.2.0
VisionPic3: /usr/local/lib/libopencv_superres.so.3.2.0
VisionPic3: /usr/local/lib/libopencv_videostab.so.3.2.0
VisionPic3: /usr/local/lib/libopencv_viz.so.3.2.0
VisionPic3: /usr/local/lib/libopencv_objdetect.so.3.2.0
VisionPic3: /usr/local/lib/libopencv_calib3d.so.3.2.0
VisionPic3: /usr/local/lib/libopencv_features2d.so.3.2.0
VisionPic3: /usr/local/lib/libopencv_flann.so.3.2.0
VisionPic3: /usr/local/lib/libopencv_highgui.so.3.2.0
VisionPic3: /usr/local/lib/libopencv_ml.so.3.2.0
VisionPic3: /usr/local/lib/libopencv_photo.so.3.2.0
VisionPic3: /usr/local/lib/libopencv_video.so.3.2.0
VisionPic3: /usr/local/lib/libopencv_videoio.so.3.2.0
VisionPic3: /usr/local/lib/libopencv_imgcodecs.so.3.2.0
VisionPic3: /usr/local/lib/libopencv_imgproc.so.3.2.0
VisionPic3: /usr/local/lib/libopencv_core.so.3.2.0
VisionPic3: CMakeFiles/VisionPic3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/jarvis/Desktop/RobotVision/Vision project1/VisionPic3/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable VisionPic3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/VisionPic3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/VisionPic3.dir/build: VisionPic3

.PHONY : CMakeFiles/VisionPic3.dir/build

CMakeFiles/VisionPic3.dir/requires: CMakeFiles/VisionPic3.dir/src/main.cpp.o.requires

.PHONY : CMakeFiles/VisionPic3.dir/requires

CMakeFiles/VisionPic3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/VisionPic3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/VisionPic3.dir/clean

CMakeFiles/VisionPic3.dir/depend:
	cd "/home/jarvis/Desktop/RobotVision/Vision project1/VisionPic3/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/jarvis/Desktop/RobotVision/Vision project1/VisionPic3" "/home/jarvis/Desktop/RobotVision/Vision project1/VisionPic3" "/home/jarvis/Desktop/RobotVision/Vision project1/VisionPic3/cmake-build-debug" "/home/jarvis/Desktop/RobotVision/Vision project1/VisionPic3/cmake-build-debug" "/home/jarvis/Desktop/RobotVision/Vision project1/VisionPic3/cmake-build-debug/CMakeFiles/VisionPic3.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/VisionPic3.dir/depend
