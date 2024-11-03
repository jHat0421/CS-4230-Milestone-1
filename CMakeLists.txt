# CMake Standards
cmake_minimum_required(VERSION 3.10)
project(ChessGame)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define Source Files
set(SOURCE_FILES
    src/main.cpp
    src/chess_game.cpp
    src/chess_board.cpp
)

# Include directories for headers
include_directories(${CMAKE_SOURCE_DIR}/src)

# Main executable for the chess game
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Compilation Settings
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
endif()

# Add GoogleTest
# Specify the path to GoogleTest directory (adjust the path as necessary)
add_subdirectory(${CMAKE_SOURCE_DIR}/googletest)

# Enable Testing
enable_testing()

# Define library for chess functionality
add_library(chess_lib src/chess_board.cpp src/chess_game.cpp)

# Test executable
add_executable(runTests tests/chess_board_test.cpp)

# Link the test executable against GoogleTest and the chess library
target_link_libraries(runTests gtest gtest_main chess_lib)

# Register tests with CMake
add_test(NAME ChessBoardTests COMMAND runTests)
