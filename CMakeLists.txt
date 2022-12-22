cmake_minimum_required(VERSION 3.23)
project(EQP)

set(CMAKE_CXX_STANDARD 20)

add_executable(EQP src/main.cpp)
include_directories(include)
add_subdirectory(test)

#GTest
enable_testing()
add_subdirectory(libs/gtest-1.12.1)
include_directories(libs/gtest-1.12.1/include)

set(LIBRARIES)
foreach (LIBRARY ${LIBRARIES})
    add_subdirectory("libs/${LIBRARY}")
endforeach (LIBRARY)
target_link_libraries(EQP ${LIBRARIES})
