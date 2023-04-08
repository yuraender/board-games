cmake_minimum_required(VERSION 3.23)
project(BGTest)

add_executable(BGTest test.cpp)

enable_testing()

target_link_libraries(BGTest gtest gtest_main)
add_test(BGTest BGTest)
