project(
    runner
    LANGUAGES CXX
)

set(HEADERS
    include/runner/sample.hpp

    # files added automatically using vxsw
    include/runner/config/test_stage.hpp
    include/runner/config/enums/parallel_strategy_type.hpp
    include/runner/config/enums/parallel_strategy_type_json_integration.hpp
    include/runner/config/test_case.hpp
    include/runner/config/test_fixture.hpp
    # end of vxsw managed section
)
set(SOURCES
    src/sample.cpp

    # files added automatically using vxsw
    src/config/test_stage.cpp
    src/config/enums/parallel_strategy_type.cpp
    src/config/test_case.cpp
    src/config/test_fixture.cpp
    # end of vxsw managed section
)
set(TESTS
    tests/sample.test.cpp

    # files added automatically using vxsw
    tests/config/test_stage.test.cpp
    tests/config/enums/parallel_strategy_type.test.cpp
    tests/config/test_case.test.cpp
    tests/config/test_fixture.test.cpp
    # end of vxsw managed section
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
        vortex::core
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
