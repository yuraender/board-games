cmake_minimum_required(VERSION 3.23)
project(BoardGames)

set(CMAKE_CXX_STANDARD 20)

add_executable(BoardGames src/main.cpp src/board.cpp src/eqp.cpp)
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
target_link_libraries(BoardGames ${LIBRARIES})
