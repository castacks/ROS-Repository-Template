cmake_minimum_required(VERSION 3.8)
project(new_package)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

message(STATUS "Build type: " ${CMAKE_BUILD_TYPE})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -Wunused-variable")
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_CXX_STANDARD 20)

# link libs only when needed
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--as-needed")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--as-needed")

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake) # for third-party
                                                           # library finding

# Compile as C++20
add_compile_options(-std=c++20)

# Dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(ament_cmake_ros REQUIRED)

# ROS 2 package dependencies
find_package(rclcpp REQUIRED)
list(APPEND AMENT_DEPENDENCIES rclcpp)

find_package(rclpy REQUIRED)
list(APPEND AMENT_DEPENDENCIES rclpy)

find_package(action_msgs REQUIRED)
list(APPEND AMENT_DEPENDENCIES action_msgs)

find_package(geometry_msgs REQUIRED)
list(APPEND AMENT_DEPENDENCIES geometry_msgs)

find_package(sensor_msgs REQUIRED)
list(APPEND AMENT_DEPENDENCIES sensor_msgs)

find_package(std_msgs REQUIRED)
list(APPEND AMENT_DEPENDENCIES std_msgs)

find_package(tf2_ros REQUIRED)
list(APPEND AMENT_DEPENDENCIES tf2_ros)

# self-defined package dependencies
find_package(cv_bridge_customize REQUIRED)
list(APPEND AMENT_DEPENDENCIES cv_bridge_customize)

find_package(file_utils REQUIRED)
list(APPEND AMENT_DEPENDENCIES file_utils)

# Boost
find_package(Boost REQUIRED)
list(APPEND INCLUDE_LIST ${Boost_INCLUDE_DIRS})
list(APPEND LIB_LIST ${Boost_LIBRARIES})

# Gflags
find_package(Gflags REQUIRED)
list(APPEND INCLUDE_LIST ${GFLAGS_INCLUDE_DIRS})
list(APPEND LIB_LIST ${GFLAGS_LIBRARIES})

# Glog
find_package(Glog REQUIRED)
list(APPEND INCLUDE_LIST ${GLOG_INCLUDE_DIRS})
list(APPEND LIB_LIST ${GLOG_LIBRARIES})

# GTest
find_package(GTest REQUIRED)
list(APPEND INCLUDE_LIST ${GTEST_INCLUDE_DIRS})
list(APPEND LIB_LIST GTest::gtest)

# OpenCV
find_package(OpenCV 4 REQUIRED)
list(APPEND INCLUDE_LIST ${OpenCV_INCLUDE_DIRS})
list(APPEND LIB_LIST ${OpenCV_LIBS})

# C++ include and library
include_directories(include ${INCLUDE_LIST})

add_library(${PROJECT_NAME} SHARED src/NewPackageLibrary.cpp)
target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                         $<INSTALL_INTERFACE:include>)
ament_target_dependencies(${PROJECT_NAME} ${AMENT_DEPENDENCIES})
target_link_libraries(${PROJECT_NAME} ${LIB_LIST})
list(APPEND LIB_LIST ${PROJECT_NAME})

add_executable(${PROJECT_NAME}_node src/${PROJECT_NAME}_node.cpp)
target_include_directories(
  ${PROJECT_NAME}_node
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include>)
ament_target_dependencies(${PROJECT_NAME}_node ${AMENT_DEPENDENCIES})
target_link_libraries(${PROJECT_NAME}_node ${LIB_LIST})

# Visibility macros
target_compile_definitions(${PROJECT_NAME}
                           PUBLIC "${PROJECT_NAME}_BUILDING_LIBRARY")

# Installation and exports
install(DIRECTORY include/ DESTINATION include)

install(
  TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_node
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME})

ament_export_include_directories(include ${INCLUDE_LIST})
ament_export_libraries(${PROJECT_NAME})
ament_export_targets(export_${PROJECT_NAME})

ament_python_install_package(${PROJECT_NAME})
install(PROGRAMS scripts/${PROJECT_NAME}_node.py
        DESTINATION lib/${PROJECT_NAME})

# Install launch files
install(DIRECTORY launch DESTINATION share/${PROJECT_NAME})

# Install config files
install(DIRECTORY config/ DESTINATION share/${PROJECT_NAME}/config)

ament_package()
