set(TESTS
    tests/sample.test.cpp
)

set(PROJECT_NAME sample-integration-tests)

add_executable(${PROJECT_NAME}
    ${TESTS}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Catch2::Catch2WithMain    
)

catch_discover_tests(${PROJECT_NAME})
