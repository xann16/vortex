project(
    core
    LANGUAGES CXX
)

set(HEADERS
    include/core/common/types.hpp
    include/core/settings/static_settings_data_storage.hpp
    include/core/settings/json/any_settings.hpp
    include/core/settings/json/document_repository.hpp
    include/core/settings/json/settings_provider.hpp
)
set(SOURCES
    src/common/types.cpp
    src/settings/static_settings_data_storage.cpp
    src/settings/json/any_settings.cpp
    src/settings/json/document_repository.cpp
    src/settings/json/settings_provider.cpp
)
set(TESTS
    tests/common/types.test.cpp
    tests/settings/static_settings_data_storage.test.cpp
    tests/settings/json/any_settings.test.cpp
    tests/settings/json/document_repository.test.cpp
    tests/settings/json/settings_provider.test.cpp
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
        nlohmann_json::nlohmann_json
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
