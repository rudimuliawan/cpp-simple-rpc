cmake_minimum_required(VERSION 3.20)

project(simple-buffer)

set(CMAKE_CXX_STANDARD 20)
set(LIB_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/simple-buffer.cpp"
)
add_library(simple-buffer
    STATIC
        ${LIB_SOURCES}
)
target_include_directories(simple-buffer
    PUBLIC
        inc
)

# Unit Test
option(ENABLE_UNIT_TESTS "Download test framework and build test executable" OFF)
if (ENABLE_UNIT_TESTS)
    if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/conaninfo.txt)
        list(PREPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_BINARY_DIR}")
    endif()
    find_package(GTest 1.10.0 REQUIRED COMPONENTS)
    enable_testing()

    set(TEST_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/tests/main.cpp"
    )
    add_executable(simple-buffer-tests ${TEST_SOURCES})
    target_compile_features(simple-buffer-tests
        PRIVATE
        cxx_std_17
    )
    target_link_libraries(simple-buffer-tests
        PRIVATE
            simple-buffer
            GTest::GTest
    )
    add_test(
        NAME simple-buffer-tests
        COMMAND $<TARGET_FILE:simple-buffer-tests>
    )
ENDIF()