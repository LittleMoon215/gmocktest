cmake_minimum_required(VERSION 3.0.0)

project(untitled VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core REQUIRED)
find_package(GTest REQUIRED)

enable_testing()
#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(${PROJECT_NAME} main.cpp
                               catch.hpp
        StateMachine.hpp StateMachine.cpp)

target_link_libraries(${PROJECT_NAME} Qt5::Core GTest::GTest gmock_main gmock)
