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
CMAKE_COMMAND = /home/tera/clion-2017.2.2/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/tera/clion-2017.2.2/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tera/Desktop/RobotVision/VisionPic1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tera/Desktop/RobotVision/VisionPic1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/VisionPic1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/VisionPic1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/VisionPic1.dir/flags.make

CMakeFiles/VisionPic1.dir/src/main.cpp.o: CMakeFiles/VisionPic1.dir/flags.make
CMakeFiles/VisionPic1.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tera/Desktop/RobotVision/VisionPic1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/VisionPic1.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/VisionPic1.dir/src/main.cpp.o -c /home/tera/Desktop/RobotVision/VisionPic1/src/main.cpp

CMakeFiles/VisionPic1.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VisionPic1.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tera/Desktop/RobotVision/VisionPic1/src/main.cpp > CMakeFiles/VisionPic1.dir/src/main.cpp.i

CMakeFiles/VisionPic1.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VisionPic1.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tera/Desktop/RobotVision/VisionPic1/src/main.cpp -o CMakeFiles/VisionPic1.dir/src/main.cpp.s

CMakeFiles/VisionPic1.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/VisionPic1.dir/src/main.cpp.o.requires

CMakeFiles/VisionPic1.dir/src/main.cpp.o.provides: CMakeFiles/VisionPic1.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/VisionPic1.dir/build.make CMakeFiles/VisionPic1.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/VisionPic1.dir/src/main.cpp.o.provides

CMakeFiles/VisionPic1.dir/src/main.cpp.o.provides.build: CMakeFiles/VisionPic1.dir/src/main.cpp.o


# Object files for target VisionPic1
VisionPic1_OBJECTS = \
"CMakeFiles/VisionPic1.dir/src/main.cpp.o"

# External object files for target VisionPic1
VisionPic1_EXTERNAL_OBJECTS =

VisionPic1: CMakeFiles/VisionPic1.dir/src/main.cpp.o
VisionPic1: CMakeFiles/VisionPic1.dir/build.make
VisionPic1: /usr/local/lib/libopencv_shape.so.3.2.0
VisionPic1: /usr/local/lib/libopencv_stitching.so.3.2.0
VisionPic1: /usr/local/lib/libopencv_superres.so.3.2.0
VisionPic1: /usr/local/lib/libopencv_videostab.so.3.2.0
VisionPic1: /usr/local/lib/libopencv_viz.so.3.2.0
VisionPic1: /usr/local/lib/libopencv_objdetect.so.3.2.0
VisionPic1: /usr/local/lib/libopencv_calib3d.so.3.2.0
VisionPic1: /usr/local/lib/libopencv_features2d.so.3.2.0
VisionPic1: /usr/local/lib/libopencv_flann.so.3.2.0
VisionPic1: /usr/local/lib/libopencv_highgui.so.3.2.0
VisionPic1: /usr/local/lib/libopencv_ml.so.3.2.0
VisionPic1: /usr/local/lib/libopencv_photo.so.3.2.0
VisionPic1: /usr/local/lib/libopencv_video.so.3.2.0
VisionPic1: /usr/local/lib/libopencv_videoio.so.3.2.0
VisionPic1: /usr/local/lib/libopencv_imgcodecs.so.3.2.0
VisionPic1: /usr/local/lib/libopencv_imgproc.so.3.2.0
VisionPic1: /usr/local/lib/libopencv_core.so.3.2.0
VisionPic1: CMakeFiles/VisionPic1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tera/Desktop/RobotVision/VisionPic1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable VisionPic1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/VisionPic1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/VisionPic1.dir/build: VisionPic1

.PHONY : CMakeFiles/VisionPic1.dir/build

CMakeFiles/VisionPic1.dir/requires: CMakeFiles/VisionPic1.dir/src/main.cpp.o.requires

.PHONY : CMakeFiles/VisionPic1.dir/requires

CMakeFiles/VisionPic1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/VisionPic1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/VisionPic1.dir/clean

CMakeFiles/VisionPic1.dir/depend:
	cd /home/tera/Desktop/RobotVision/VisionPic1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tera/Desktop/RobotVision/VisionPic1 /home/tera/Desktop/RobotVision/VisionPic1 /home/tera/Desktop/RobotVision/VisionPic1/cmake-build-debug /home/tera/Desktop/RobotVision/VisionPic1/cmake-build-debug /home/tera/Desktop/RobotVision/VisionPic1/cmake-build-debug/CMakeFiles/VisionPic1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/VisionPic1.dir/depend

