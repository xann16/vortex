project(
    turb
    LANGUAGES CXX
)

set(HEADERS
    include/turb/sample.hpp


    # files added automatically using vxsw
    include/turb/legacy/settings/exec_settings.hpp
    include/turb/legacy/settings/turb_settings.hpp
    include/turb/legacy/settings/parameters.hpp
    include/turb/legacy/settings/metadata.hpp
)
set(SOURCES
    src/sample.cpp


    # files added automatically using vxsw
    src/legacy/settings/exec_settings.cpp
    src/legacy/settings/turb_settings.cpp
    src/legacy/settings/parameters.cpp
    src/legacy/settings/metadata.cpp
)
set(TESTS
    tests/sample.test.cpp


    # files added automatically using vxsw
    tests/legacy/settings/exec_settings.test.cpp
    tests/legacy/settings/turb_settings.test.cpp
    tests/legacy/settings/parameters.test.cpp
    tests/legacy/settings/metadata.test.cpp
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
        MPI::MPI_CXX
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

if (BUILD_TESTING)

    add_executable(${PROJECT_NAME}-unit-tests
        ${TESTS}
    )

    target_link_libraries(${PROJECT_NAME}-unit-tests
        PRIVATE
            ${PROJECT_NAME}
            Catch2::Catch2WithMain    
    )

    catch_discover_tests(${PROJECT_NAME}-unit-tests)

endif()