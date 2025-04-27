add_library(tokenizer SHARED tokenizer.cpp)
target_compile_options(tokenizer PUBLIC ${BFCK_LIB_FLAGS})

add_library(parser SHARED parser.cpp)
target_compile_options(parser PUBLIC ${BFCK_LIB_FLAGS})
target_link_libraries(parser PUBLIC tokenizer)

add_library(utility SHARED utility.cpp)
target_compile_options(utility PUBLIC ${BFCK_LIB_FLAGS})

add_library(reader SHARED reader.cpp)
target_link_libraries(reader PUBLIC utility)
target_compile_options(reader PUBLIC ${BFCK_LIB_FLAGS})

# Compiler
add_executable(ccbf_comp compiler.cpp)
target_compile_options(ccbf_comp PUBLIC ${BFCK_LIB_FLAGS})

if(SHOW_ASM)
    message("Showing assembly output for compiled bf sources")
    target_compile_definitions(ccbf_comp PUBLIC SHOW_ASM)
endif()

target_link_libraries(ccbf_comp PUBLIC tokenizer reader utility)

# Interpreter
add_library(bfck_interpreter SHARED interpreter.cpp)
target_link_libraries(bfck_interpreter PUBLIC reader parser utility)
target_compile_options(bfck_interpreter PUBLIC ${BFCK_LIB_FLAGS})

# Main EXE
add_executable(ccbf main.cpp)
target_link_libraries(ccbf PRIVATE bfck_interpreter)
target_compile_options(ccbf PRIVATE ${BFCK_EXE_FLAGS})

if (BUILD_TEST)
    message("Building unit tests")
    add_subdirectory(test)
endif()
