cmake_minimum_required(VERSION 2.8)
project( VisionPic1 )
find_package( OpenCV 3 REQUIRED )
add_executable(VisionPic1 src/main.cpp )
target_link_libraries( VisionPic1 ${OpenCV_LIBS})

