project(
    turb
    LANGUAGES CXX
)

set(HEADERS
    include/turb/legacy/settings_provider.hpp
    include/turb/legacy/sim_id.hpp

    # files added automatically using vxsw
    include/turb/legacy/settings/settings.hpp
    include/turb/legacy/settings/enums/forcing_type.hpp
    include/turb/legacy/settings/enums/forcing_type_json_integration.hpp
    include/turb/legacy/settings/enums/drag_type.hpp
    include/turb/legacy/settings/enums/drag_type_json_integration.hpp
    include/turb/legacy/settings/parameters.hpp
    include/turb/legacy/settings/enums/sim_method.hpp
    include/turb/legacy/settings/enums/sim_method_json_integration.hpp
    include/turb/legacy/settings/enums/particle_mode.hpp
    include/turb/legacy/settings/enums/particle_mode_json_integration.hpp
    include/turb/legacy/settings/enums/gravity_mode.hpp
    include/turb/legacy/settings/enums/gravity_mode_json_integration.hpp
    include/turb/legacy/settings/enums/particle_twc_kernel_type.hpp
    include/turb/legacy/settings/enums/particle_twc_kernel_type_json_integration.hpp
    include/turb/legacy/settings/metadata.hpp
    include/turb/legacy/settings/execution_settings.hpp
    include/turb/legacy/settings/providers/json_settings_provider.hpp
    # end of vxsw managed section
)
set(SOURCES
    src/legacy/settings_provider.cpp
    src/legacy/sim_id.cpp

    # files added automatically using vxsw
    src/legacy/settings/settings.cpp
    src/legacy/settings/enums/forcing_type.cpp
    src/legacy/settings/enums/drag_type.cpp
    src/legacy/settings/parameters.cpp
    src/legacy/settings/enums/sim_method.cpp
    src/legacy/settings/enums/particle_mode.cpp
    src/legacy/settings/enums/gravity_mode.cpp
    src/legacy/settings/enums/particle_twc_kernel_type.cpp
    src/legacy/settings/metadata.cpp
    src/legacy/settings/execution_settings.cpp
    src/legacy/settings/providers/json_settings_provider.cpp
    # end of vxsw managed section
)
set(TESTS
    tests/legacy/settings_provider.test.cpp
    tests/legacy/sim_id.test.cpp

    # files added automatically using vxsw
    tests/legacy/settings/settings.test.cpp
    tests/legacy/settings/enums/forcing_type.test.cpp
    tests/legacy/settings/enums/drag_type.test.cpp
    tests/legacy/settings/parameters.test.cpp
    tests/legacy/settings/enums/sim_method.test.cpp
    tests/legacy/settings/enums/particle_mode.test.cpp
    tests/legacy/settings/enums/gravity_mode.test.cpp
    tests/legacy/settings/enums/particle_twc_kernel_type.test.cpp
    tests/legacy/settings/metadata.test.cpp
    tests/legacy/settings/execution_settings.test.cpp
    tests/legacy/settings/providers/json_settings_provider.test.cpp
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
        vortex::runner
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
