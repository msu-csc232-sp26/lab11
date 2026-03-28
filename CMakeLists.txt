cmake_minimum_required(VERSION 3.16.3)

# ------------------------------------------------------------------------------
# Project & Policies
# ------------------------------------------------------------------------------
project(change-me LANGUAGES CXX)

# Generate compile_commands.json for IDEs (clangd, etc.)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Keep existing policy usage for FetchContent timestamp behavior
if (CMAKE_VERSION GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif ()

# ------------------------------------------------------------------------------
# Options
# ------------------------------------------------------------------------------
# Homework/Lab flag you already had
set(IS_HW FALSE CACHE BOOL "Is this a homework build?")

# Enable/disable compiler warnings and errors
option(ENABLE_WARNINGS "Enable common compiler warnings" ON)
option(WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)

# Sanitizers (non-MSVC; typically only in Debug)
option(ENABLE_ASAN "Enable AddressSanitizer (Debug builds)" OFF)
option(ENABLE_UBSAN "Enable UndefinedBehaviorSanitizer (Debug builds)" OFF)

# Task toggles (additional to header toggles; convenient for CI/instructors)
option(TEST_TASK1 "Enable Task 1 tests (unique_ptr)" ON)
option(TEST_TASK2 "Enable Task 2 tests (shared_ptr)" OFF)
option(TEST_TASK3 "Enable Task 3 tests (weak_ptr)" OFF)

# Docs
option(BUILD_DOC "Build documentation" ON)

# ------------------------------------------------------------------------------
# Helper: Apply per-target settings (C++ standard, warnings, sanitizers)
# ------------------------------------------------------------------------------
function(apply_project_settings target_name)
    # Require C++20 at target level
    target_compile_features(${target_name} PRIVATE cxx_std_20)

    if (ENABLE_WARNINGS)
        if (MSVC)
            target_compile_options(${target_name} PRIVATE /W4)
            if (WARNINGS_AS_ERRORS)
                target_compile_options(${target_name} PRIVATE /WX)
            endif ()
        else ()
            target_compile_options(${target_name} PRIVATE -Wall -Wextra -Wpedantic)
            if (WARNINGS_AS_ERRORS)
                target_compile_options(${target_name} PRIVATE -Werror)
            endif ()
        endif ()
    endif ()

    # Sanitizers are typically only useful for Debug builds and non-MSVC
    if (CMAKE_BUILD_TYPE STREQUAL "Debug" AND NOT MSVC)
        if (ENABLE_ASAN)
            target_compile_options(${target_name} PRIVATE -fsanitize=address)
            target_link_options(${target_name} PRIVATE -fsanitize=address)
        endif ()
        if (ENABLE_UBSAN)
            target_compile_options(${target_name} PRIVATE -fsanitize=undefined)
            target_link_options(${target_name} PRIVATE -fsanitize=undefined)
        endif ()
    endif ()
endfunction()

# ------------------------------------------------------------------------------
# Sources
# ------------------------------------------------------------------------------
# Keep your existing expanded_templates.cpp in all three executables
set(SRC_MAIN_FILES
        src/main/cpp/main.cpp
        src/main/cpp/expanded_templates.cpp
)

set(SRC_DEMO_FILES
        src/main/cpp/demo.cpp
        src/main/cpp/expanded_templates.cpp
)

set(SRC_UNIT_TESTS
        src/test/cpp/unit_tests.cpp
        src/main/cpp/expanded_templates.cpp
)

# ------------------------------------------------------------------------------
# Executables (main & demo)
# ------------------------------------------------------------------------------
add_executable(main ${SRC_MAIN_FILES})
add_executable(demo ${SRC_DEMO_FILES})

# Only expose public headers; do not add src/main/cpp as an include directory
target_include_directories(main PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
target_include_directories(demo PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)

apply_project_settings(main)
apply_project_settings(demo)

# ------------------------------------------------------------------------------
# GoogleTest via FetchContent
# ------------------------------------------------------------------------------
set(GOOGLE_TEST_ARCHIVE "v1.17.0")  # version pin consistent with your repo
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/${GOOGLE_TEST_ARCHIVE}.zip
)
# On MSVC, use same CRT across gtest and the project
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

# ------------------------------------------------------------------------------
# Unit tests: keep custom main (so do NOT link gtest_main)
# ------------------------------------------------------------------------------
add_executable(unit_tests ${SRC_UNIT_TESTS})
target_include_directories(unit_tests PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${CMAKE_CURRENT_LIST_DIR}/src/test/cpp
)
apply_project_settings(unit_tests)

# Link GoogleTest libraries (no gtest_main because unit_tests.cpp provides main())
target_link_libraries(unit_tests PRIVATE GTest::gtest GTest::gmock)

# Compile-time toggles for tasks (optional convenience for instructors/CI)
target_compile_definitions(unit_tests PRIVATE
        TEST_TASK1=$<BOOL:${TEST_TASK1}>
        TEST_TASK2=$<BOOL:${TEST_TASK2}>
        TEST_TASK3=$<BOOL:${TEST_TASK3}>
)
# If you also want demo/main to reflect toggles at build time:
target_compile_definitions(main PRIVATE
        TEST_TASK1=$<BOOL:${TEST_TASK1}>
        TEST_TASK2=$<BOOL:${TEST_TASK2}>
        TEST_TASK3=$<BOOL:${TEST_TASK3}>
)
target_compile_definitions(demo PRIVATE
        TEST_TASK1=$<BOOL:${TEST_TASK1}>
        TEST_TASK2=$<BOOL:${TEST_TASK2}>
        TEST_TASK3=$<BOOL:${TEST_TASK3}>
)

# Auto-discover tests; works with custom main()
gtest_discover_tests(unit_tests
        WORKING_DIRECTORY $<TARGET_FILE_DIR:unit_tests>
        PROPERTIES
        ENVIRONMENT "GTEST_OUTPUT=xml:unit_test_results.xml"
)

# ------------------------------------------------------------------------------
# Resource copying (use generator expressions for multi-config generators)
# ------------------------------------------------------------------------------
# Main resources
add_custom_command(TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_LIST_DIR}/src/main/resources/main_data.txt
        $<TARGET_FILE_DIR:main>
)

# Demo resources
add_custom_command(TARGET demo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_LIST_DIR}/src/main/resources/demo_data.txt
        $<TARGET_FILE_DIR:demo>
)

# Unit test resources
foreach (fname IN ITEMS task1_test_data.txt task2_test_data.txt task3_test_data.txt)
    add_custom_command(TARGET unit_tests POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_LIST_DIR}/src/test/resources/${fname}
            $<TARGET_FILE_DIR:unit_tests>
    )
endforeach ()

if (IS_HW)
    foreach (fname IN ITEMS task4_test_data.txt task5_test_data.txt)
        add_custom_command(TARGET unit_tests PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${CMAKE_CURRENT_LIST_DIR}/src/test/resources/${fname}
                $<TARGET_FILE_DIR:unit_tests>
        )
    endforeach ()
endif ()

# ------------------------------------------------------------------------------
# Documentation (Doxygen)
# ------------------------------------------------------------------------------
find_package(Doxygen OPTIONAL_COMPONENTS dot mscgen dia)
if (DOXYGEN_FOUND AND BUILD_DOC)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/config/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    add_custom_target(doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else ()
    message(STATUS "Doxygen not found or BUILD_DOC=OFF; skipping docs")
endif ()

# ------------------------------------------------------------------------------
# Optional: Enable IPO/LTO in Release (if supported)
# ------------------------------------------------------------------------------
include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported OUTPUT ipo_error)
if (ipo_supported)
    foreach (tgt IN ITEMS main demo unit_tests)
        set_property(TARGET ${tgt} PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
    endforeach ()
else ()
    message(STATUS "IPO/LTO not supported: ${ipo_error}")
endif ()
