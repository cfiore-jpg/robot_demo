cmake_minimum_required(VERSION 3.24)
project(RobotNavigationDemo)

set(CMAKE_CXX_STANDARD 17)

add_executable(RobotNavigationDemo main.cpp)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

set(robotFolder /Users/cameronfiore/C++/ShieldAI/robot)

include_directories(RobotNavigationDemo ${robotFolder}/include)
target_link_libraries(RobotNavigationDemo ${robotFolder}/build/libRobotNavigation.dylib)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(RobotNavigationDemo ${OpenCV_LIBS})
