cmake_minimum_required(VERSION 2.8.12)

project(VisionPic1)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(VisionPic1 src/main.cpp)
target_link_libraries(VisionPic1 ${OpenCV_LIBS})
