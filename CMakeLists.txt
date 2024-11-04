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

# Git clone googletest with FetchContent:
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

# Necessary for Windows Functionality: (Prevent overriding the parent project's compiler/linker settings)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Define library for chess functionality
add_library(chess_lib src/chess_board.cpp src/chess_game.cpp)

# Test executable
add_executable(runTests tests/chess_board_test.cpp tests/chess_game_test.cpp)

# Link the test executable against GoogleTest and the chess library
target_link_libraries(runTests gtest gtest_main chess_lib)

# Register tests with CMake
add_test(NAME ChessBoardTests COMMAND runTests)
