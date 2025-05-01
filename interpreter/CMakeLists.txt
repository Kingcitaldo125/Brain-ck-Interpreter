add_library(bfck_tokenizer SHARED tokenizer.cpp)
target_compile_options(bfck_tokenizer PUBLIC ${BFCK_LIB_FLAGS})

add_library(bfck_parser SHARED parser.cpp)
target_compile_options(bfck_parser PUBLIC ${BFCK_LIB_FLAGS})
target_link_libraries(bfck_parser PUBLIC bfck_tokenizer)

add_library(bfck_utility SHARED utility.cpp)
target_compile_options(bfck_utility PUBLIC ${BFCK_LIB_FLAGS})

add_library(bfck_reader SHARED reader.cpp)
target_link_libraries(bfck_reader PUBLIC bfck_utility)
target_compile_options(bfck_reader PUBLIC ${BFCK_LIB_FLAGS})

# Compiler
add_executable(ccbf_comp compiler.cpp)
target_compile_options(ccbf_comp PUBLIC ${BFCK_LIB_FLAGS})

if(SHOW_ASM)
    message("Showing assembly output for compiled bf sources")
    target_compile_definitions(ccbf_comp PUBLIC SHOW_ASM)
endif()

target_link_libraries(ccbf_comp PUBLIC bfck_tokenizer bfck_reader bfck_utility)

# Interpreter
add_library(bfck_interpreter SHARED interpreter.cpp)
target_link_libraries(bfck_interpreter PUBLIC bfck_reader bfck_parser bfck_utility)
target_compile_options(bfck_interpreter PUBLIC ${BFCK_LIB_FLAGS})

# Main EXE
add_executable(ccbf main.cpp)
target_link_libraries(ccbf PRIVATE bfck_interpreter)
target_compile_options(ccbf PRIVATE ${BFCK_EXE_FLAGS})

if (BUILD_TEST)
    message("Building unit tests")
    add_subdirectory(test)
endif()

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Generate CMake package config files
configure_package_config_file(
    ${CMAKE_SOURCE_DIR}/cmake/BrainfckConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/BrainfckConfig.cmake
    INSTALL_DESTINATION  ${CMAKE_INSTALL_LIBDIR}/cmake/brainfck
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/BrainfckConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Install targets
install(
    TARGETS bfck_reader bfck_parser bfck_tokenizer bfck_utility
    EXPORT BRAINFCKTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Install target export
install(EXPORT BRAINFCKTargets
    FILE BRAINFCKTargets.cmake
    NAMESPACE BRAINFCK::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/brainfck
)

# Install package config files
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/BrainfckConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/BrainfckConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/brainfck
)

# Install headers
file(GLOB BFckHeaders false "*.hpp")

install(FILES
    ${BFckHeaders}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/brainfck
)

include(CPack)
