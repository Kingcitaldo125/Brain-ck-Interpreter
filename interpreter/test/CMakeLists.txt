find_package(Catch2 CONFIG REQUIRED)

add_executable(parse_test parse_test.cpp)
target_link_libraries(parse_test PRIVATE bfck_interpreter Catch2::Catch2 Catch2::Catch2WithMain)
target_include_directories(parse_test PRIVATE ${CMAKE_SOURCE_DIR}/interpreter)

enable_testing()

add_test(NAME ParseTest COMMAND parse_test)
