cmake_minimum_required(VERSION 3.0.2)
project(sort_cpp)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++17")

# find_package(catkin REQUIRED)
# set (OpenCV_DIR /workspace/docker-opencv/opencv-3.4.5/build/)
find_package(OpenCV REQUIRED)
message(STATUS " > version ${OPENCV_VERSION}")
if(NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV not found")
endif()


# catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES sort_cpp
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
#)

include_directories(
${CMAKE_SOURCE_DIR}/src
${PROJECT_SOURCE_DIR}/src
${OPENCV_INCLUDE_DIR}
# include
# ${catkin_INCLUDE_DIRS}
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

## Declare a C++ library
add_library(${PROJECT_NAME} SHARED
src/KalmanTracker.cpp
src/Hungarian.cpp
)
## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}
${OpenCV_LIBS}
)


### Build ###

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
## Declare a C++ executable

add_executable(yolov3-demo src/yolov3.cpp)
target_link_libraries(yolov3-demo ${PROJECT_NAME} opencv_core opencv_video opencv_videoio opencv_imgproc opencv_imgcodecs opencv_highgui glog vitis_ai_library-xnnpp vitis_ai_library-model_config protobuf vitis_ai_library-dpu_task)

add_executable(yolov3-video src/yolov3-video.cpp)
target_link_libraries(yolov3-video ${PROJECT_NAME} opencv_core opencv_video opencv_videoio opencv_imgproc opencv_imgcodecs opencv_highgui glog vitis_ai_library-xnnpp vitis_ai_library-model_config protobuf vitis_ai_library-dpu_task)

add_executable(video_test src/test_video.cpp)
target_link_libraries(video_test ${PROJECT_NAME} ${OpenCV_LIBS})

add_executable(yolov3-sort src/yolov3-sort.cpp)
target_link_libraries(yolov3-sort ${PROJECT_NAME} opencv_core opencv_video opencv_videoio opencv_imgproc opencv_imgcodecs opencv_highgui glog vitis_ai_library-xnnpp vitis_ai_library-model_config protobuf vitis_ai_library-dpu_task)


# #/bin/sh
# CXX=${CXX:-g++}
# $CXX -std=c++17 -O3 -I. -o demo_yolov3 demo_yolov3.cpp -lopencv_core -
# lopencv_video -lopencv_videoio -lopencv_imgproc -lopencv_imgcodecs -
# lopencv_highgui -lglog -lxnnpp-xnnpp -lvitis_ai_library-model_config -
# lprotobuf -lvitis_ai_library-dpu_task