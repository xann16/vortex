project(
    turb-basic-sample
    LANGUAGES CXX
)

set(HEADERS "")
set(SOURCES
    basic-sample.cpp
)

add_executable(${PROJECT_NAME}
    ${HEADERS}
    ${SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        vortex::core)