add_library(parser SHARED parser.cpp)
target_compile_options(parser PUBLIC ${BFCK_LIB_FLAGS})

add_library(utility SHARED utility.cpp)
target_compile_options(utility PUBLIC ${BFCK_LIB_FLAGS})

add_library(reader SHARED reader.cpp)
target_link_libraries(reader PUBLIC utility)
target_compile_options(reader PUBLIC ${BFCK_LIB_FLAGS})

add_library(bfck_interpreter SHARED interpreter.cpp)
target_link_libraries(bfck_interpreter PUBLIC reader parser utility)
target_compile_options(bfck_interpreter PUBLIC ${BFCK_LIB_FLAGS})

add_executable(ccbf main.cpp)
target_link_libraries(ccbf PRIVATE bfck_interpreter)
target_compile_options(ccbf PRIVATE ${BFCK_EXE_FLAGS})

if (BUILD_TEST)
    message("Building unit tests")
    add_subdirectory(test)
endif()
