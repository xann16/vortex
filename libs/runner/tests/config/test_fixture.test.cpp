// 
// Unit test source file auto-generated by VORTEX SETTINGS WIZARD
// 
// TODO: Just testing
// 

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <nlohmann/json.hpp>

#include "runner/config/test_fixture.hpp"

TEST_CASE( "TestFixture - basic test", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::runner::config::TestFixture{ &obj };

    REQUIRE( !s.is_empty() );

    auto data_p = s.data();
    auto anys = s.as_any();

    REQUIRE( !anys.is_empty() );

    auto ss = vortex::runner::config::TestFixture{ anys };

    REQUIRE( !ss.is_empty() );
    REQUIRE( data_p != nullptr );
    REQUIRE( obj == *data_p );
    REQUIRE( *anys.data() == *data_p );
    REQUIRE( *ss.data() == *data_p );
}

TEST_CASE( "TestFixture - basic empty test", "[settings]" )
{
    auto s = vortex::runner::config::TestFixture{};

    REQUIRE( s.is_empty() );

    auto anys = s.as_any();

    REQUIRE( anys.is_empty() );

    auto ss = vortex::runner::config::TestFixture{ anys };

    REQUIRE( ss.is_empty() );
    REQUIRE( s.data() == nullptr );
    REQUIRE( anys.data() == nullptr );
    REQUIRE( ss.data() == nullptr );
}

TEST_CASE( "TestFixture - conversion to string", "[settings][.][!mayfail]" )
{
    // TODO - add conversion to string tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "TestFixture - conversion to string - display all", "[settings][.][!mayfail]" )
{
    // TODO - add conversion to string tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "TestFixture - conversion to string - extra indent size", "[settings][.][!mayfail]" )
{
    // TODO - add conversion to string tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "TestFixture - conversion to string - extra indent level", "[settings][.][!mayfail]" )
{
    // TODO - add conversion to string tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "TestFixture - conversion to string for empty", "[settings][.][!mayfail]" )
{
    // TODO - add conversion to string tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "TestFixture - merge", "[settings][.][!mayfail]" )
{
    // TODO - add merge tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "TestFixture - merge with removal", "[settings][.][!mayfail]" )
{
    // TODO - add merge tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "TestFixture - merge with empties", "[settings][.][!mayfail]" )
{
    // TODO - add merge tests for generated setting classes
    REQUIRE( false );
}

// "name" property

TEST_CASE( "TestFixture - property: \"name\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "name", "stest" } };
    auto s = vortex::runner::config::TestFixture{ &obj };
    auto s_null = vortex::runner::config::TestFixture{};

    auto value = s.name();
    auto default_value = s_null.name();

    REQUIRE( value == "stest" );
    REQUIRE( default_value == std::string_view{} );

    REQUIRE( s.has_name_set() );
    REQUIRE( !s_null.has_name_set() );
}

// "root_path" property

TEST_CASE( "TestFixture - property: \"root_path\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "root_path", "ptest" } };
    auto s = vortex::runner::config::TestFixture{ &obj };
    auto s_null = vortex::runner::config::TestFixture{};

    auto value = s.root_path();
    auto default_value = s_null.root_path();

    REQUIRE( value == "ptest" );
    REQUIRE( default_value == "." );

    REQUIRE( s.has_root_path_set() );
    REQUIRE( !s_null.has_root_path_set() );
}

// "default_settings" property

TEST_CASE( "TestFixture - property: \"default_settings\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "default_settings", { { "x", "y" } } } };
    auto s = vortex::runner::config::TestFixture{ &obj };
    auto s_null = vortex::runner::config::TestFixture{};

    auto value = s.default_settings();
    auto default_value = s_null.default_settings();

    REQUIRE( !value.is_empty() );
    REQUIRE( value.data()->at( "x" ) == "y" );
    REQUIRE( default_value.is_empty() );

    REQUIRE( s.has_default_settings_set() );
    REQUIRE( !s_null.has_default_settings_set() );
}

// "test_cases" property

TEST_CASE( "TestFixture - property: \"test_cases\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "test_cases", { { "x", "y" } } } };
    auto s = vortex::runner::config::TestFixture{ &obj };
    auto s_null = vortex::runner::config::TestFixture{};

    auto value = s.test_cases();
    auto default_value = s_null.test_cases();

    REQUIRE( !value.is_empty() );
    REQUIRE( value.data()->at( "x" ) == "y" );
    REQUIRE( default_value.is_empty() );

    REQUIRE( s.has_test_cases_set() );
    REQUIRE( !s_null.has_test_cases_set() );
}

// "test_stages" property

TEST_CASE( "TestFixture - property: \"test_stages\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "test_stages", { { "x", "y" } } } };
    auto s = vortex::runner::config::TestFixture{ &obj };
    auto s_null = vortex::runner::config::TestFixture{};

    auto value = s.test_stages();
    auto default_value = s_null.test_stages();

    REQUIRE( !value.is_empty() );
    REQUIRE( value.data()->at( "x" ) == "y" );
    REQUIRE( default_value.is_empty() );

    REQUIRE( s.has_test_stages_set() );
    REQUIRE( !s_null.has_test_stages_set() );
}


