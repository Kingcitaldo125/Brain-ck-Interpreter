add_library(reader SHARED reader.cpp)
add_library(utility SHARED utility.cpp)

add_library(bfck SHARED parser.cpp)
target_link_libraries(bfck PUBLIC reader utility)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE bfck)
