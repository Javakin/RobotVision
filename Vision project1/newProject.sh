#!/bin/bash
####################################
#
# This script will create a new project for RoVi1
#
####################################

	DIR=$2
	PROJTYPE="${1,,}"

if [[ "$PROJTYPE" == "" ]]; then
	DIR=.
	PROJTYPE=.
	echo "No Input Type given "
	echo "correct syntax is ./newProject.sh <project type (-r or -v) <Project folder name>"
	exit
else if [[ "$DIR" == "" ]]; then
	DIR=.
	PROJTYPE=.
	echo "No Folder given."
	echo "correct syntax is ./newProject.sh <project type (-r or -v) <Project folder name>"
	exit
	fi

	if [ "$PROJTYPE" != "-r" ] && [ "$PROJTYPE" != "-v" ]; then
		echo "unknown project type"
		echo "exiting..."
	exit
	fi

if [ -d "$DIR" ]; then
	echo "Project folder already exists"
	exit
else
	echo "Making Folders/ files"
	mkdir $DIR
	cd $DIR

	mkdir src
	mkdir build
	touch src/main.cpp
	touch CMakeLists.txt
#create CMakeLists.txt

	case $PROJTYPE in
	"-v" )

	echo "adding Vision files"
#create CMakeLists.txt
	cat  >CMakeLists.txt << EOL
cmake_minimum_required(VERSION 2.8)
project( $DIR )
find_package( OpenCV 3 REQUIRED )
add_executable($DIR src/main.cpp )
target_link_libraries( $DIR \${OpenCV_LIBS})

EOL
	echo "CMakeLists.txt written"

#create a default src/main.cpp
	cat >src/main.cpp <<EOL
/*
 * RoVi1
 * Example application to load and display an image
 */

// v1.0-4-gdfe246a

#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
    // Parse command line arguments
    cv::CommandLineParser parser(argc, argv,
        "{help   |            | print this message}"
        "{@image | ../book.jpg | image path}"
    );

    if (parser.has("help")) {
        parser.printMessage();
        return 0;
    }

    // Load image
    std::string filename = parser.get<std::string>("@image");
    cv::Mat img = cv::imread(filename);

    if (img.empty()) {
        std::cout << "Input image not found at '" << filename << "'\n";
        return 1;
    }

    // Show the image
    cv::imshow("Image", img);
    cv::waitKey();

    return 0;
}
EOL
	echo "src/main.cpp written successfully"
	;;
	"-r")
	echo "adding RobWork files"
#create CMakeLists.txt
	cat  >CMakeLists.txt << EOL
# Test CMake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)

# The name of the project
PROJECT($DIR)
MESSAGE(\${$DIR} ":")

# Used to resolve absolute path names
SET(ROOT \${CMAKE_CURRENT_SOURCE_DIR})

# Use c++11
SET(CMAKE_CXX_FLAGS "-std=c++11 \${CMAKE_CXX_FLAGS}")

# Set the RobWork root (edit in .bashrc if necessary)
SET(RW_ROOT \$ENV{RW_ROOT})

# Verbose mode prints more info when doing make
set(CMAKE_VERBOSE_MAKEFILE false)

# Set build type to release
SET(CMAKE_BUILD_TYPE Release)
MESSAGE("-- Build type: " \${CMAKE_BUILD_TYPE})

# Use RobWork
SET(RobWork_DIR ${RW_ROOT}/cmake)
FIND_PACKAGE(RobWork REQUIRED)
INCLUDE_DIRECTORIES( \${ROBWORK_INCLUDE_DIRS} )
LINK_DIRECTORIES( \${ROBWORK_LIBRARY_DIRS} )

# Add the source files to build
SET(SrcFiles src/main.cpp)

# The shared library to build:
ADD_EXECUTABLE($DIR \${SrcFiles})
TARGET_LINK_LIBRARIES($DIR \${ROBWORK_LIBRARIES})

MESSAGE(\${PROJECT_NAME} " done!")


EOL
	echo "CMakeLists.txt written"

#create a default src/main.cpp
	cat >src/main.cpp <<EOL
#include <iostream>
#include <rw/math.hpp> // Pi, Deg2Rad
#include <rw/math/Q.hpp>
#include <rw/math/Transform3D.hpp>
#include <rw/math/RPY.hpp>
#include <rw/math/Vector3D.hpp>
#include <rw/math/EAA.hpp>


using namespace std;
using namespace rw::math;
int main(int argc, char** argv) {
 cout << "RobWork is ready to run" << endl;
 return 0;
}

EOL
	echo "src/main.cpp written successfully"
	;;
	*)
		echo "WARNING: unknown command."
		echo "No files written, Exiting..."
	exit
	;;
esac
#CMAKE file generation and Executable execution
cd build
	cmake ../
	echo "Cmake generation Success"
	make
	echo "Project: $DIR creation Success"


fi
fi
