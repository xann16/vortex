// 
// Unit test source file auto-generated by VORTEX SETTINGS WIZARD
// 
// TODO: Just testing
// 

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <nlohmann/json.hpp>
#include "turb/legacy/settings/stat/execution_settings_conversion.hpp"

TEST_CASE( "ExecutionSettings - property: \"job_name\" - static", "[settings]" )
{
    nlohmann::json obj = { { "job_name", "stest" } };
    auto ds = vortex::core::settings::StaticSettingsDataStorage{};

    auto s = vortex::turb::legacy::settings::ExecutionSettings{ &obj };
    auto s_null = vortex::turb::legacy::settings::ExecutionSettings{};

    auto value = s.job_name();
    auto default_value = s_null.job_name();

    auto ss = vortex::turb::legacy::settings::to_static_unchecked( s, ds );
    auto ss_null = vortex::turb::legacy::settings::to_static_unchecked( s_null, ds );

    auto svalue = ss.job_name();
    auto default_svalue = ss_null.job_name();

    REQUIRE( value == svalue );
    REQUIRE( default_value == default_svalue );

    REQUIRE( svalue == "stest" );
    REQUIRE( default_svalue == "default_job" );
}

TEST_CASE( "ExecutionSettings - property: \"grant_no\" - static", "[settings]" )
{
    nlohmann::json obj = { { "grant_no", "stest" } };
    auto ds = vortex::core::settings::StaticSettingsDataStorage{};

    auto s = vortex::turb::legacy::settings::ExecutionSettings{ &obj };
    auto s_null = vortex::turb::legacy::settings::ExecutionSettings{};

    auto value = s.grant_no();
    auto default_value = s_null.grant_no();

    auto ss = vortex::turb::legacy::settings::to_static_unchecked( s, ds );
    auto ss_null = vortex::turb::legacy::settings::to_static_unchecked( s_null, ds );

    auto svalue = ss.grant_no();
    auto default_svalue = ss_null.grant_no();

    REQUIRE( value == svalue );
    REQUIRE( default_value == default_svalue );

    REQUIRE( svalue == "stest" );
    REQUIRE( default_svalue == std::string_view{} );
}

TEST_CASE( "ExecutionSettings - property: \"cpu_node_count\" - static", "[settings]" )
{
    nlohmann::json obj = { { "cpu_node_count", 8l } };
    auto ds = vortex::core::settings::StaticSettingsDataStorage{};

    auto s = vortex::turb::legacy::settings::ExecutionSettings{ &obj };
    auto s_null = vortex::turb::legacy::settings::ExecutionSettings{};

    auto value = s.cpu_node_count();
    auto default_value = s_null.cpu_node_count();

    auto ss = vortex::turb::legacy::settings::to_static_unchecked( s, ds );
    auto ss_null = vortex::turb::legacy::settings::to_static_unchecked( s_null, ds );

    auto svalue = ss.cpu_node_count();
    auto default_svalue = ss_null.cpu_node_count();

    REQUIRE( value == svalue );
    REQUIRE( default_value == default_svalue );

    REQUIRE( static_cast< vortex::i32 >( svalue ) == 8l );
    REQUIRE( static_cast< vortex::i32 >( default_svalue ) == 1 );
}

TEST_CASE( "ExecutionSettings - property: \"wct_limit\" - static", "[settings]" )
{
    nlohmann::json obj = { { "wct_limit", 8.2 } };
    auto ds = vortex::core::settings::StaticSettingsDataStorage{};

    auto s = vortex::turb::legacy::settings::ExecutionSettings{ &obj };
    auto s_null = vortex::turb::legacy::settings::ExecutionSettings{};

    auto value = s.wct_limit();
    auto default_value = s_null.wct_limit();

    auto ss = vortex::turb::legacy::settings::to_static_unchecked( s, ds );
    auto ss_null = vortex::turb::legacy::settings::to_static_unchecked( s_null, ds );

    auto svalue = ss.wct_limit();
    auto default_svalue = ss_null.wct_limit();

    REQUIRE( value == svalue );
    REQUIRE( default_value == default_svalue );

    REQUIRE_THAT( static_cast< vortex::f64 >( svalue ), Catch::Matchers::WithinAbs( 8.2, 1e-05 ) );
    REQUIRE_THAT( static_cast< vortex::f64 >( default_svalue ), Catch::Matchers::WithinAbs( 60.0, 1e-05 ) );
}

TEST_CASE( "ExecutionSettings - property: \"process_count\" - static", "[settings]" )
{
    nlohmann::json obj = { { "process_count", 8l } };
    auto ds = vortex::core::settings::StaticSettingsDataStorage{};

    auto s = vortex::turb::legacy::settings::ExecutionSettings{ &obj };
    auto s_null = vortex::turb::legacy::settings::ExecutionSettings{};

    auto value = s.process_count();
    auto default_value = s_null.process_count();

    auto ss = vortex::turb::legacy::settings::to_static_unchecked( s, ds );
    auto ss_null = vortex::turb::legacy::settings::to_static_unchecked( s_null, ds );

    auto svalue = ss.process_count();
    auto default_svalue = ss_null.process_count();

    REQUIRE( value == svalue );
    REQUIRE( default_value == default_svalue );

    REQUIRE( static_cast< vortex::i32 >( svalue ) == 8l );
    REQUIRE( static_cast< vortex::i32 >( default_svalue ) == 1 );
}

TEST_CASE( "ExecutionSettings - property: \"is_node_overcommit_enabled\" - static", "[settings]" )
{
    nlohmann::json obj = { { "is_node_overcommit_enabled", true } };
    auto ds = vortex::core::settings::StaticSettingsDataStorage{};

    auto s = vortex::turb::legacy::settings::ExecutionSettings{ &obj };
    auto s_null = vortex::turb::legacy::settings::ExecutionSettings{};

    auto value = s.is_node_overcommit_enabled();
    auto default_value = s_null.is_node_overcommit_enabled();

    auto ss = vortex::turb::legacy::settings::to_static_unchecked( s, ds );
    auto ss_null = vortex::turb::legacy::settings::to_static_unchecked( s_null, ds );

    auto svalue = ss.is_node_overcommit_enabled();
    auto default_svalue = ss_null.is_node_overcommit_enabled();

    REQUIRE( value == svalue );
    REQUIRE( default_value == default_svalue );

    REQUIRE( svalue == true );
    REQUIRE( default_svalue == bool{} );
}


