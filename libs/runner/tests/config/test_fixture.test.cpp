// 
// Unit test source file auto-generated by VORTEX SETTINGS WIZARD
// 
// TODO: Just testing
// 

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <nlohmann/json.hpp>

#include "runner/config/test_fixture.hpp"

TEST_CASE( "TestFixture - Sample Test", "[sample]" )
{
    vortex::runner::config::TestFixture( nullptr );

    REQUIRE( true );
}

// "name" property

TEST_CASE( "TestFixture - property: \"name\" - getter", "[settings]" )
{
    auto obj = nlohmann::json{ { "name", "stest" } };
    auto obj_p = &obj;
    auto s = vortex::runner::config::TestFixture{ obj_p };
    auto s_null = vortex::runner::config::TestFixture{ nullptr };

    auto value = s.name();
    auto default_value = s_null.name();

    REQUIRE( value == "stest" );
    REQUIRE( default_value == std::string_view{} );
}

// "root_path" property

TEST_CASE( "TestFixture - property: \"root_path\" - getter", "[settings]" )
{
    auto obj = nlohmann::json{ { "root_path", "ptest" } };
    auto obj_p = &obj;
    auto s = vortex::runner::config::TestFixture{ obj_p };
    auto s_null = vortex::runner::config::TestFixture{ nullptr };

    auto value = s.root_path();
    auto default_value = s_null.root_path();

    REQUIRE( value == "ptest" );
    REQUIRE( default_value == "." );
}

// "default_settings" property

TEST_CASE( "TestFixture - property: \"default_settings\" - getter", "[settings]" )
{
    auto s_null = vortex::runner::config::TestFixture{ nullptr };


    REQUIRE_THROWS_AS( s_null.default_settings(), std::runtime_error );
}

// "test_cases" property

TEST_CASE( "TestFixture - property: \"test_cases\" - getter", "[settings]" )
{
    auto s_null = vortex::runner::config::TestFixture{ nullptr };

    auto default_value = s_null.test_cases();

    REQUIRE( default_value == nullptr );
}

// "test_stages" property

TEST_CASE( "TestFixture - property: \"test_stages\" - getter", "[settings]" )
{
    auto s_null = vortex::runner::config::TestFixture{ nullptr };

    auto default_value = s_null.test_stages();

    REQUIRE( default_value == nullptr );
}


