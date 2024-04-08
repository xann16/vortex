project(
    core
    LANGUAGES CXX
)

set(HEADERS
    include/core/sample.hpp
)
set(SOURCES
    src/sample.cpp
)

add_library(${PROJECT_NAME}
    STATIC
    ${HEADERS}
    ${SOURCES}
)
add_library(${CMAKE_PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        rapidjson
        fftw::fftw
        Catch2::Catch2WithMain
        MPI::MPI_CXX
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
