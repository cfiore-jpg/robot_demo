cmake_minimum_required(VERSION 3.24)
project(RobotNavigationDemo)

set(CMAKE_CXX_STANDARD 17)

add_executable(RobotNavigationDemo
        main.cpp
        ../RobotNavigation/src/Map.cpp
        ../RobotNavigation/src/Robot.cpp
        ../RobotNavigation/include/Robot.h)

#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

set(RobotNavigationFolder ${CMAKE_CURRENT_SOURCE_DIR}/../RobotNavigation)
include_directories(RobotNavigationDemo ${RobotNavigationFolder}/include)
target_link_libraries(RobotNavigationDemo ${RobotNavigationFolder}/cmake-build-release/libRobotNavigation.dylib)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(RobotNavigationDemo ${OpenCV_LIBS})
