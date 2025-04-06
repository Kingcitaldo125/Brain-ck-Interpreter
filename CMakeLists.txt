cmake_minimum_required(VERSION 3.16)

project(brainfck_interpreter_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

option(DEBUG "Enable Debugging" false)

if(DEBUG)
    message("Building with Debug")
    add_compile_definitions(DEBUG)
endif()

add_subdirectory(${CMAKE_SOURCE_DIR}/interpreter/)
