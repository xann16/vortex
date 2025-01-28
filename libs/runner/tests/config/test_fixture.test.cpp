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

TEST_CASE( "TestFixture - equality and inequality operators", "[settings][.][!mayfail]" )
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

TEST_CASE( "TestFixture - property: \"name\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::runner::config::TestFixture{ &obj };
    auto s_null = vortex::runner::config::TestFixture{};

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

TEST_CASE( "TestFixture - property: \"root_path\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::runner::config::TestFixture{ &obj };
    auto s_null = vortex::runner::config::TestFixture{};

    const auto sv = std::string_view{ "sv" };
    const auto str = std::string{ "str" };
    const auto cstr = "cstr";

    REQUIRE( !s.has_root_path_set() );
    REQUIRE( !s_null.has_root_path_set() );

    REQUIRE_NOTHROW( s.reset_root_path() );
    REQUIRE_NOTHROW( s_null.reset_root_path() );

    REQUIRE_THROWS_AS( s_null.set_root_path( sv ), std::runtime_error );
    REQUIRE_THROWS_AS( s_null.set_root_path( str ), std::runtime_error );
    REQUIRE_THROWS_AS( s_null.set_root_path( cstr ), std::runtime_error );
    REQUIRE_THROWS_AS( s_null.set_root_path( std::string{ "mvstr" } ), std::runtime_error );

    s.set_root_path( sv );
    REQUIRE( s.has_root_path_set() );
    REQUIRE( s.root_path() == "sv" );

    s.set_root_path( str );
    REQUIRE( s.has_root_path_set() );
    REQUIRE( s.root_path() == "str" );

    s.set_root_path( cstr );
    REQUIRE( s.has_root_path_set() );
    REQUIRE( s.root_path() == "cstr" );

    s.set_root_path( std::string{ "mvstr" } );
    REQUIRE( s.has_root_path_set() );
    REQUIRE( s.root_path() == "mvstr" );

    s.reset_root_path();
    REQUIRE( !s.has_root_path_set() );

}

// "default_settings" property

TEST_CASE( "TestFixture - property: \"default_settings\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "default_settings", { { "x", "y"} } } };
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

TEST_CASE( "TestFixture - property: \"default_settings\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::runner::config::TestFixture{ &obj };
    auto s_null = vortex::runner::config::TestFixture{};

    nlohmann::json vobj = nlohmann::json::object();
    const auto value = vortex::core::settings::json::AnySettings{ &vobj };
    const auto nvalue = vortex::core::settings::json::AnySettings{};

    REQUIRE( !s.has_default_settings_set() );
    REQUIRE( !s_null.has_default_settings_set() );

    REQUIRE_NOTHROW( s.reset_default_settings() );
    REQUIRE_NOTHROW( s_null.reset_default_settings() );

    REQUIRE_THROWS_AS( s_null.set_default_settings( value ), std::runtime_error );

    s.set_default_settings( value );
    REQUIRE( s.has_default_settings_set() );
    REQUIRE( *( s.default_settings().data() ) == nlohmann::json::object() );

    s.set_default_settings( nvalue );
    REQUIRE( !s.has_default_settings_set() );

    s.set_default_settings( value );

    s.reset_default_settings();
    REQUIRE( !s.has_default_settings_set() );

}

// "test_cases" property

TEST_CASE( "TestFixture - property: \"test_cases\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "test_cases", { { { "x", "y"} }, { { "x", "y"} }, { { "x", "y"} } } } };
    auto s = vortex::runner::config::TestFixture{ &obj };
    auto s_null = vortex::runner::config::TestFixture{};

    auto value = s.test_cases();
    auto default_value = s_null.test_cases();

    REQUIRE( !value.empty() );
    REQUIRE( value.size() == 3ull );
    REQUIRE( !value[ 0 ].is_empty() );
    REQUIRE( value[ 0 ].data()->at( "x" ) == "y" );
    REQUIRE( !value[ 1 ].is_empty() );
    REQUIRE( value[ 1 ].data()->at( "x" ) == "y" );
    REQUIRE( !value[ 2 ].is_empty() );
    REQUIRE( value[ 2 ].data()->at( "x" ) == "y" );
    REQUIRE( default_value.empty() );

    REQUIRE( s.has_test_cases_set() );
    REQUIRE( !s_null.has_test_cases_set() );
}

TEST_CASE( "TestFixture - property: \"test_cases\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::runner::config::TestFixture{ &obj };
    auto s_null = vortex::runner::config::TestFixture{};

    nlohmann::json vobj = nlohmann::json::object();
    const auto value = std::vector< vortex::runner::config::TestCase >{ vortex::runner::config::TestCase{ &vobj }, vortex::runner::config::TestCase{ &vobj }, vortex::runner::config::TestCase{ &vobj } };

    REQUIRE( !s.has_test_cases_set() );
    REQUIRE( !s_null.has_test_cases_set() );

    REQUIRE_NOTHROW( s.reset_test_cases() );
    REQUIRE_NOTHROW( s_null.reset_test_cases() );

    REQUIRE_THROWS_AS( s_null.set_test_cases( value ), std::runtime_error );
    REQUIRE_THROWS_AS( s_null.set_test_cases( std::vector< vortex::runner::config::TestCase >{ value } ), std::runtime_error );
    REQUIRE_THROWS_AS( s_null.set_test_cases( { vortex::runner::config::TestCase{ &vobj }, vortex::runner::config::TestCase{ &vobj }, vortex::runner::config::TestCase{ &vobj } } ), std::runtime_error );

    s.reset_test_cases();
    REQUIRE( !s.has_test_cases_set() );

    s.set_test_cases( value );
    REQUIRE( s.has_test_cases_set() );
    REQUIRE( s.test_cases() == value );

    s.reset_test_cases();
    REQUIRE( !s.has_test_cases_set() );

    s.set_test_cases( std::vector< vortex::runner::config::TestCase >{ value } );
    REQUIRE( s.has_test_cases_set() );
    REQUIRE( s.test_cases() == value );

    s.reset_test_cases();
    REQUIRE( !s.has_test_cases_set() );

    s.set_test_cases( { vortex::runner::config::TestCase{ &vobj }, vortex::runner::config::TestCase{ &vobj }, vortex::runner::config::TestCase{ &vobj } } );
    REQUIRE( s.has_test_cases_set() );
    REQUIRE( s.test_cases() == value );

    s.reset_test_cases();
    REQUIRE( !s.has_test_cases_set() );

}

// "test_stages" property

TEST_CASE( "TestFixture - property: \"test_stages\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "test_stages", { { { "x", "y"} }, { { "x", "y"} }, { { "x", "y"} } } } };
    auto s = vortex::runner::config::TestFixture{ &obj };
    auto s_null = vortex::runner::config::TestFixture{};

    auto value = s.test_stages();
    auto default_value = s_null.test_stages();

    REQUIRE( !value.empty() );
    REQUIRE( value.size() == 3ull );
    REQUIRE( !value[ 0 ].is_empty() );
    REQUIRE( value[ 0 ].data()->at( "x" ) == "y" );
    REQUIRE( !value[ 1 ].is_empty() );
    REQUIRE( value[ 1 ].data()->at( "x" ) == "y" );
    REQUIRE( !value[ 2 ].is_empty() );
    REQUIRE( value[ 2 ].data()->at( "x" ) == "y" );
    REQUIRE( default_value.empty() );

    REQUIRE( s.has_test_stages_set() );
    REQUIRE( !s_null.has_test_stages_set() );
}

TEST_CASE( "TestFixture - property: \"test_stages\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::runner::config::TestFixture{ &obj };
    auto s_null = vortex::runner::config::TestFixture{};

    nlohmann::json vobj = nlohmann::json::object();
    const auto value = std::vector< vortex::runner::config::TestStage >{ vortex::runner::config::TestStage{ &vobj }, vortex::runner::config::TestStage{ &vobj }, vortex::runner::config::TestStage{ &vobj } };

    REQUIRE( !s.has_test_stages_set() );
    REQUIRE( !s_null.has_test_stages_set() );

    REQUIRE_NOTHROW( s.reset_test_stages() );
    REQUIRE_NOTHROW( s_null.reset_test_stages() );

    REQUIRE_THROWS_AS( s_null.set_test_stages( value ), std::runtime_error );
    REQUIRE_THROWS_AS( s_null.set_test_stages( std::vector< vortex::runner::config::TestStage >{ value } ), std::runtime_error );
    REQUIRE_THROWS_AS( s_null.set_test_stages( { vortex::runner::config::TestStage{ &vobj }, vortex::runner::config::TestStage{ &vobj }, vortex::runner::config::TestStage{ &vobj } } ), std::runtime_error );

    s.reset_test_stages();
    REQUIRE( !s.has_test_stages_set() );

    s.set_test_stages( value );
    REQUIRE( s.has_test_stages_set() );
    REQUIRE( s.test_stages() == value );

    s.reset_test_stages();
    REQUIRE( !s.has_test_stages_set() );

    s.set_test_stages( std::vector< vortex::runner::config::TestStage >{ value } );
    REQUIRE( s.has_test_stages_set() );
    REQUIRE( s.test_stages() == value );

    s.reset_test_stages();
    REQUIRE( !s.has_test_stages_set() );

    s.set_test_stages( { vortex::runner::config::TestStage{ &vobj }, vortex::runner::config::TestStage{ &vobj }, vortex::runner::config::TestStage{ &vobj } } );
    REQUIRE( s.has_test_stages_set() );
    REQUIRE( s.test_stages() == value );

    s.reset_test_stages();
    REQUIRE( !s.has_test_stages_set() );

}


