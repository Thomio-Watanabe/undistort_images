cmake_minimum_required(VERSION 2.6)
project(undistort_images)

find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    message("-- Found OpenCV")
endif(OpenCV_FOUND)

add_executable(undistort_images src/main.cpp src/undistort.cpp)
target_link_libraries(undistort_images ${OpenCV_LIBS})
