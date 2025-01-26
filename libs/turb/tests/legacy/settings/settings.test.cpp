// 
// Unit test source file auto-generated by VORTEX SETTINGS WIZARD
// 
// TODO: Just testing
// 

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <nlohmann/json.hpp>

#include "turb/legacy/settings/settings.hpp"

TEST_CASE( "Settings - basic test", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::turb::legacy::settings::Settings{ &obj };

    REQUIRE( !s.is_empty() );

    auto data_p = s.data();
    auto anys = s.as_any();

    REQUIRE( !anys.is_empty() );

    auto ss = vortex::turb::legacy::settings::Settings{ anys };

    REQUIRE( !ss.is_empty() );
    REQUIRE( data_p != nullptr );
    REQUIRE( obj == *data_p );
    REQUIRE( *anys.data() == *data_p );
    REQUIRE( *ss.data() == *data_p );
}

TEST_CASE( "Settings - basic empty test", "[settings]" )
{
    auto s = vortex::turb::legacy::settings::Settings{};

    REQUIRE( s.is_empty() );

    auto anys = s.as_any();

    REQUIRE( anys.is_empty() );

    auto ss = vortex::turb::legacy::settings::Settings{ anys };

    REQUIRE( ss.is_empty() );
    REQUIRE( s.data() == nullptr );
    REQUIRE( anys.data() == nullptr );
    REQUIRE( ss.data() == nullptr );
}

TEST_CASE( "Settings - conversion to string", "[settings][.][!mayfail]" )
{
    // TODO - add conversion to string tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "Settings - conversion to string - display all", "[settings][.][!mayfail]" )
{
    // TODO - add conversion to string tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "Settings - conversion to string - extra indent size", "[settings][.][!mayfail]" )
{
    // TODO - add conversion to string tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "Settings - conversion to string - extra indent level", "[settings][.][!mayfail]" )
{
    // TODO - add conversion to string tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "Settings - conversion to string for empty", "[settings][.][!mayfail]" )
{
    // TODO - add conversion to string tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "Settings - merge", "[settings][.][!mayfail]" )
{
    // TODO - add merge tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "Settings - merge with removal", "[settings][.][!mayfail]" )
{
    // TODO - add merge tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "Settings - merge with empties", "[settings][.][!mayfail]" )
{
    // TODO - add merge tests for generated setting classes
    REQUIRE( false );
}

// "metadata" property

TEST_CASE( "Settings - property: \"metadata\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "metadata", { { "x", "y" } } } };
    auto s = vortex::turb::legacy::settings::Settings{ &obj };
    auto s_null = vortex::turb::legacy::settings::Settings{};

    auto value = s.metadata();
    auto default_value = s_null.metadata();

    REQUIRE( !value.is_empty() );
    REQUIRE( value.data()->at( "x" ) == "y" );
    REQUIRE( default_value.is_empty() );

    REQUIRE( s.has_metadata_set() );
    REQUIRE( !s_null.has_metadata_set() );
}

TEST_CASE( "Settings - property: \"metadata\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::turb::legacy::settings::Settings{ &obj };
    auto s_null = vortex::turb::legacy::settings::Settings{};

    nlohmann::json vobj = nlohmann::json::object();
    const auto value = vortex::turb::legacy::settings::Metadata{ &vobj };
    const auto nvalue = vortex::turb::legacy::settings::Metadata{};

    REQUIRE( !s.has_metadata_set() );
    REQUIRE( !s_null.has_metadata_set() );

    REQUIRE_NOTHROW( s.reset_metadata() );
    REQUIRE_NOTHROW( s_null.reset_metadata() );

    REQUIRE_THROWS_AS( s_null.set_metadata( value ), std::runtime_error );

    s.set_metadata( value );
    REQUIRE( s.has_metadata_set() );
    REQUIRE( *( s.metadata().data() ) == nlohmann::json::object() );

    s.set_metadata( nvalue );
    REQUIRE( !s.has_metadata_set() );

    s.set_metadata( value );

    s.reset_metadata();
    REQUIRE( !s.has_metadata_set() );

}

// "parameters" property

TEST_CASE( "Settings - property: \"parameters\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "parameters", { { "x", "y" } } } };
    auto s = vortex::turb::legacy::settings::Settings{ &obj };
    auto s_null = vortex::turb::legacy::settings::Settings{};

    auto value = s.parameters();
    auto default_value = s_null.parameters();

    REQUIRE( !value.is_empty() );
    REQUIRE( value.data()->at( "x" ) == "y" );
    REQUIRE( default_value.is_empty() );

    REQUIRE( s.has_parameters_set() );
    REQUIRE( !s_null.has_parameters_set() );
}

TEST_CASE( "Settings - property: \"parameters\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::turb::legacy::settings::Settings{ &obj };
    auto s_null = vortex::turb::legacy::settings::Settings{};

    nlohmann::json vobj = nlohmann::json::object();
    const auto value = vortex::turb::legacy::settings::Parameters{ &vobj };
    const auto nvalue = vortex::turb::legacy::settings::Parameters{};

    REQUIRE( !s.has_parameters_set() );
    REQUIRE( !s_null.has_parameters_set() );

    REQUIRE_NOTHROW( s.reset_parameters() );
    REQUIRE_NOTHROW( s_null.reset_parameters() );

    REQUIRE_THROWS_AS( s_null.set_parameters( value ), std::runtime_error );

    s.set_parameters( value );
    REQUIRE( s.has_parameters_set() );
    REQUIRE( *( s.parameters().data() ) == nlohmann::json::object() );

    s.set_parameters( nvalue );
    REQUIRE( !s.has_parameters_set() );

    s.set_parameters( value );

    s.reset_parameters();
    REQUIRE( !s.has_parameters_set() );

}

// "execution_settings" property

TEST_CASE( "Settings - property: \"execution_settings\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "execution_settings", { { "x", "y" } } } };
    auto s = vortex::turb::legacy::settings::Settings{ &obj };
    auto s_null = vortex::turb::legacy::settings::Settings{};

    auto value = s.execution_settings();
    auto default_value = s_null.execution_settings();

    REQUIRE( !value.is_empty() );
    REQUIRE( value.data()->at( "x" ) == "y" );
    REQUIRE( default_value.is_empty() );

    REQUIRE( s.has_execution_settings_set() );
    REQUIRE( !s_null.has_execution_settings_set() );
}

TEST_CASE( "Settings - property: \"execution_settings\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::turb::legacy::settings::Settings{ &obj };
    auto s_null = vortex::turb::legacy::settings::Settings{};

    nlohmann::json vobj = nlohmann::json::object();
    const auto value = vortex::turb::legacy::settings::ExecutionSettings{ &vobj };
    const auto nvalue = vortex::turb::legacy::settings::ExecutionSettings{};

    REQUIRE( !s.has_execution_settings_set() );
    REQUIRE( !s_null.has_execution_settings_set() );

    REQUIRE_NOTHROW( s.reset_execution_settings() );
    REQUIRE_NOTHROW( s_null.reset_execution_settings() );

    REQUIRE_THROWS_AS( s_null.set_execution_settings( value ), std::runtime_error );

    s.set_execution_settings( value );
    REQUIRE( s.has_execution_settings_set() );
    REQUIRE( *( s.execution_settings().data() ) == nlohmann::json::object() );

    s.set_execution_settings( nvalue );
    REQUIRE( !s.has_execution_settings_set() );

    s.set_execution_settings( value );

    s.reset_execution_settings();
    REQUIRE( !s.has_execution_settings_set() );

}


