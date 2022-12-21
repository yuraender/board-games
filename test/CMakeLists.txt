cmake_minimum_required(VERSION 3.23)
project(EQPTest)

add_executable(EQPTest test.cpp)

enable_testing()

target_link_libraries(EQPTest gtest gtest_main)
add_test(EQPTest EQPTest)
