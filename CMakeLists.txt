cmake_minimum_required(VERSION 3.16)
project(lab11 LANGUAGES CXX)


# ------------------------------------------------------------
# Assignment task toggles
# ------------------------------------------------------------
option(TEST_TASK1 "Enable Task 1 tests" ON)
option(TEST_TASK2 "Enable Task 2 tests" ON)
option(TEST_TASK3 "Enable Task 3 tests" ON)

if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24")
    cmake_policy(SET CMP0135 NEW)
endif ()

# ------------------------------------------------------------
# Global Settings
# ------------------------------------------------------------
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------------------------------------
# CI / Instructor Options
# ------------------------------------------------------------
option(BUILD_APPS "Build main/demo executables" ON)
option(BUILD_TESTS "Build unit tests" ON)
option(BUILD_DOCS "Build Doxygen docs" OFF)
option(ENABLE_ASAN "Enable AddressSanitizer" OFF)

# ------------------------------------------------------------
# Helper: compiler warnings
# ------------------------------------------------------------
function(apply_warnings tgt)
    if (MSVC)
        target_compile_options(${tgt} PRIVATE /W4)
    else ()
        target_compile_options(${tgt} PRIVATE -Wall -Wextra -Wpedantic)
    endif ()
endfunction()

# ------------------------------------------------------------
# Sources
# ------------------------------------------------------------
set(SRC_COMMON
        src/main/cpp/expanded_templates.cpp
)

set(SRC_MAIN
        src/main/cpp/main.cpp
        ${SRC_COMMON}
)

set(SRC_DEMO
        src/main/cpp/demo.cpp
        ${SRC_COMMON}
)

set(SRC_TESTS
        src/test/cpp/unit_tests.cpp
        ${SRC_COMMON}
)

# ------------------------------------------------------------
# Applications (OFF in CI)
# ------------------------------------------------------------
if (BUILD_APPS)
    add_executable(main ${SRC_MAIN})
    add_executable(demo ${SRC_DEMO})

    target_include_directories(main PRIVATE include)
    target_include_directories(demo PRIVATE include)

    apply_warnings(main)
    apply_warnings(demo)
endif ()

# ------------------------------------------------------------
# GoogleTest
# ------------------------------------------------------------
if (BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    add_executable(unit_tests ${SRC_TESTS})
    target_compile_definitions(unit_tests
            PRIVATE
            TEST_TASK1=$<BOOL:${TEST_TASK1}>
            TEST_TASK2=$<BOOL:${TEST_TASK2}>
            TEST_TASK3=$<BOOL:${TEST_TASK3}>
    )
    target_include_directories(unit_tests PRIVATE
            include
            src/test/cpp
    )
    target_link_libraries(unit_tests PRIVATE
            GTest::gtest
            GTest::gmock
    )

    apply_warnings(unit_tests)

    include(GoogleTest)
    gtest_discover_tests(unit_tests)


endif ()

# ------------------------------------------------------------
# Documentation (OFF by default)
# ------------------------------------------------------------
if (BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    add_custom_target(doc
            COMMAND ${DOXYGEN_EXECUTABLE} config/Doxyfile
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif ()
