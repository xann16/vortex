// 
// Unit test source file auto-generated by VORTEX SETTINGS WIZARD
// 
// TODO: Just testing
// 

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <nlohmann/json.hpp>

#include "runner/config/test_stage.hpp"

TEST_CASE( "TestStage - basic test", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::runner::config::TestStage{ &obj };

    REQUIRE( !s.is_empty() );

    auto data_p = s.data();
    auto anys = s.as_any();

    REQUIRE( !anys.is_empty() );

    auto ss = vortex::runner::config::TestStage{ anys };

    REQUIRE( !ss.is_empty() );
    REQUIRE( data_p != nullptr );
    REQUIRE( obj == *data_p );
    REQUIRE( *anys.data() == *data_p );
    REQUIRE( *ss.data() == *data_p );
}

TEST_CASE( "TestStage - basic empty test", "[settings]" )
{
    auto s = vortex::runner::config::TestStage{};

    REQUIRE( s.is_empty() );

    auto anys = s.as_any();

    REQUIRE( anys.is_empty() );

    auto ss = vortex::runner::config::TestStage{ anys };

    REQUIRE( ss.is_empty() );
    REQUIRE( s.data() == nullptr );
    REQUIRE( anys.data() == nullptr );
    REQUIRE( ss.data() == nullptr );
}

TEST_CASE( "TestStage - conversion to string", "[settings][.][!mayfail]" )
{
    // TODO - add conversion to string tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "TestStage - conversion to string - display all", "[settings][.][!mayfail]" )
{
    // TODO - add conversion to string tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "TestStage - conversion to string - extra indent size", "[settings][.][!mayfail]" )
{
    // TODO - add conversion to string tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "TestStage - conversion to string - extra indent level", "[settings][.][!mayfail]" )
{
    // TODO - add conversion to string tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "TestStage - conversion to string for empty", "[settings][.][!mayfail]" )
{
    // TODO - add conversion to string tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "TestStage - merge", "[settings][.][!mayfail]" )
{
    // TODO - add merge tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "TestStage - merge with removal", "[settings][.][!mayfail]" )
{
    // TODO - add merge tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "TestStage - merge with empties", "[settings][.][!mayfail]" )
{
    // TODO - add merge tests for generated setting classes
    REQUIRE( false );
}

// "name" property

TEST_CASE( "TestStage - property: \"name\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "name", "stest" } };
    auto s = vortex::runner::config::TestStage{ &obj };
    auto s_null = vortex::runner::config::TestStage{};

    auto value = s.name();
    auto default_value = s_null.name();

    REQUIRE( value == "stest" );
    REQUIRE( default_value == std::string_view{} );

    REQUIRE( s.has_name_set() );
    REQUIRE( !s_null.has_name_set() );
}

TEST_CASE( "TestStage - property: \"name\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::runner::config::TestStage{ &obj };
    auto s_null = vortex::runner::config::TestStage{};

    const auto sv = std::string_view{ "sv" };
    const auto str = std::string{ "str" };
    const auto cstr = "cstr";

    REQUIRE( !s.has_name_set() );
    REQUIRE( !s_null.has_name_set() );

    REQUIRE_NOTHROW( s.reset_name() );
    REQUIRE_NOTHROW( s_null.reset_name() );

    REQUIRE_THROWS_AS( s_null.set_name( sv ), std::runtime_error );
    REQUIRE_THROWS_AS( s_null.set_name( str ), std::runtime_error );
    REQUIRE_THROWS_AS( s_null.set_name( cstr ), std::runtime_error );
    REQUIRE_THROWS_AS( s_null.set_name( std::string{ "mvstr" } ), std::runtime_error );

    s.set_name( sv );
    REQUIRE( s.has_name_set() );
    REQUIRE( s.name() == "sv" );

    s.set_name( str );
    REQUIRE( s.has_name_set() );
    REQUIRE( s.name() == "str" );

    s.set_name( cstr );
    REQUIRE( s.has_name_set() );
    REQUIRE( s.name() == "cstr" );

    s.set_name( std::string{ "mvstr" } );
    REQUIRE( s.has_name_set() );
    REQUIRE( s.name() == "mvstr" );

    s.reset_name();
    REQUIRE( !s.has_name_set() );

}

// "settings" property

TEST_CASE( "TestStage - property: \"settings\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "settings", { { "x", "y" } } } };
    auto s = vortex::runner::config::TestStage{ &obj };
    auto s_null = vortex::runner::config::TestStage{};

    auto value = s.settings();
    auto default_value = s_null.settings();

    REQUIRE( !value.is_empty() );
    REQUIRE( value.data()->at( "x" ) == "y" );
    REQUIRE( default_value.is_empty() );

    REQUIRE( s.has_settings_set() );
    REQUIRE( !s_null.has_settings_set() );
}

TEST_CASE( "TestStage - property: \"settings\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::runner::config::TestStage{ &obj };
    auto s_null = vortex::runner::config::TestStage{};

    nlohmann::json vobj = nlohmann::json::object();
    const auto value = vortex::core::settings::json::AnySettings{ &vobj };
    const auto nvalue = vortex::core::settings::json::AnySettings{};

    REQUIRE( !s.has_settings_set() );
    REQUIRE( !s_null.has_settings_set() );

    REQUIRE_NOTHROW( s.reset_settings() );
    REQUIRE_NOTHROW( s_null.reset_settings() );

    REQUIRE_THROWS_AS( s_null.set_settings( value ), std::runtime_error );

    s.set_settings( value );
    REQUIRE( s.has_settings_set() );
    REQUIRE( *( s.settings().data() ) == nlohmann::json::object() );

    s.set_settings( nvalue );
    REQUIRE( !s.has_settings_set() );

    s.set_settings( value );

    s.reset_settings();
    REQUIRE( !s.has_settings_set() );

}


