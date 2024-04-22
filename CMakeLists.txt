cmake_minimum_required(VERSION 3.21)

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()
set(CMAKE_CXX_EXTENSIONS OFF)

project(
    vortex
    VERSION 0.1.0
    DESCRIPTION "Experimental C++ framework for parallelizable numerical solvers focusing on computational fluid dynamics with C and Fortran bindings."
    HOMEPAGE_URL "https://github.com/xann16/vortex"
    LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(compiler-options-setup)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(setup-dependencies)

# testing - make conditional of being top level project
include(CTest)

if (BUILD_TESTING)
    include(CTest)
    include(Catch)

    enable_testing()

    add_subdirectory(tests)
endif()

add_subdirectory(libs)
add_subdirectory(samples)

add_subdirectory(extras)


