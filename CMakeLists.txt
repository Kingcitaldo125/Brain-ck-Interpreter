cmake_minimum_required(VERSION 3.16)

project(brainfck_interpreter_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

option(DEBUG "Enable Debugging" false)
option(BUILD_TEST "Enable Unit Tests" false)

if(DEBUG)
    message("Building with Debug")
    add_compile_definitions(DEBUG)
endif()

set(BFCK_EXE_FLAGS -O3 -Wall -Wextra)
set(BFCK_LIB_FLAGS -fPIC ${BFCK_EXE_FLAGS})

add_subdirectory(${CMAKE_SOURCE_DIR}/interpreter/)
