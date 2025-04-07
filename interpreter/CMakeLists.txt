add_library(parser SHARED parser.cpp)
add_library(utility SHARED utility.cpp)

add_library(reader SHARED reader.cpp)
target_link_libraries(reader PUBLIC utility)

add_library(bfck_interpreter SHARED interpreter.cpp)
target_link_libraries(bfck_interpreter PUBLIC reader parser utility)

add_executable(ccbf main.cpp)
target_link_libraries(ccbf PRIVATE bfck_interpreter)
