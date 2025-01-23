// 
// Unit test source file auto-generated by VORTEX SETTINGS WIZARD
// 
// TODO: Just testing
// 

#include <cstring>
#include <string>
#include <catch2/catch_test_macros.hpp>
#include <nlohmann/json.hpp>
#include "turb/legacy/settings/enums/gravity_mode.hpp"
#include "turb/legacy/settings/enums/gravity_mode_json_integration.hpp"

TEST_CASE( "GravityMode - conversion between enums and strings", "[sample]" )
{
    using namespace std::string_literals;

    // Testing conversions for GravityMode::None
    REQUIRE( vortex::turb::legacy::settings::to_string( vortex::turb::legacy::settings::GravityMode::None ) == "none"s );
    REQUIRE( std::strcmp( vortex::turb::legacy::settings::to_c_str( vortex::turb::legacy::settings::GravityMode::None ), "none" ) == 0 );
    REQUIRE( vortex::turb::legacy::settings::to_gravity_mode( "none" ) == vortex::turb::legacy::settings::GravityMode::None );
    REQUIRE( vortex::turb::legacy::settings::to_gravity_mode( "none"s ) == vortex::turb::legacy::settings::GravityMode::None );
    REQUIRE( vortex::turb::legacy::settings::to_gravity_mode( vortex::turb::legacy::settings::to_string( vortex::turb::legacy::settings::GravityMode::None ) ) == vortex::turb::legacy::settings::GravityMode::None );
    REQUIRE( vortex::turb::legacy::settings::to_gravity_mode( vortex::turb::legacy::settings::to_c_str( vortex::turb::legacy::settings::GravityMode::None ) ) == vortex::turb::legacy::settings::GravityMode::None );

    // Testing conversions for GravityMode::Vertical
    REQUIRE( vortex::turb::legacy::settings::to_string( vortex::turb::legacy::settings::GravityMode::Vertical ) == "vertical"s );
    REQUIRE( std::strcmp( vortex::turb::legacy::settings::to_c_str( vortex::turb::legacy::settings::GravityMode::Vertical ), "vertical" ) == 0 );
    REQUIRE( vortex::turb::legacy::settings::to_gravity_mode( "vertical" ) == vortex::turb::legacy::settings::GravityMode::Vertical );
    REQUIRE( vortex::turb::legacy::settings::to_gravity_mode( "vertical"s ) == vortex::turb::legacy::settings::GravityMode::Vertical );
    REQUIRE( vortex::turb::legacy::settings::to_gravity_mode( vortex::turb::legacy::settings::to_string( vortex::turb::legacy::settings::GravityMode::Vertical ) ) == vortex::turb::legacy::settings::GravityMode::Vertical );
    REQUIRE( vortex::turb::legacy::settings::to_gravity_mode( vortex::turb::legacy::settings::to_c_str( vortex::turb::legacy::settings::GravityMode::Vertical ) ) == vortex::turb::legacy::settings::GravityMode::Vertical );

    // Testing conversions for GravityMode::Horizontal
    REQUIRE( vortex::turb::legacy::settings::to_string( vortex::turb::legacy::settings::GravityMode::Horizontal ) == "horizontal"s );
    REQUIRE( std::strcmp( vortex::turb::legacy::settings::to_c_str( vortex::turb::legacy::settings::GravityMode::Horizontal ), "horizontal" ) == 0 );
    REQUIRE( vortex::turb::legacy::settings::to_gravity_mode( "horizontal" ) == vortex::turb::legacy::settings::GravityMode::Horizontal );
    REQUIRE( vortex::turb::legacy::settings::to_gravity_mode( "horizontal"s ) == vortex::turb::legacy::settings::GravityMode::Horizontal );
    REQUIRE( vortex::turb::legacy::settings::to_gravity_mode( vortex::turb::legacy::settings::to_string( vortex::turb::legacy::settings::GravityMode::Horizontal ) ) == vortex::turb::legacy::settings::GravityMode::Horizontal );
    REQUIRE( vortex::turb::legacy::settings::to_gravity_mode( vortex::turb::legacy::settings::to_c_str( vortex::turb::legacy::settings::GravityMode::Horizontal ) ) == vortex::turb::legacy::settings::GravityMode::Horizontal );

    // Testing conversions for values out of range
    REQUIRE( vortex::turb::legacy::settings::to_string( static_cast< vortex::turb::legacy::settings::GravityMode >( 3 ) ) == "unknown"s );
    REQUIRE( std::strcmp( vortex::turb::legacy::settings::to_c_str( static_cast< vortex::turb::legacy::settings::GravityMode >( 3 ) ), "unknown" ) == 0 );
    REQUIRE( vortex::turb::legacy::settings::to_gravity_mode( "" ) == vortex::turb::legacy::settings::GravityMode::None );
    REQUIRE( vortex::turb::legacy::settings::to_gravity_mode( ""s ) == vortex::turb::legacy::settings::GravityMode::None );
}


TEST_CASE( "GravityMode - integration with json serialization", "[sample]" )
{
    nlohmann::json none_json_from_enum = vortex::turb::legacy::settings::GravityMode::None;
    nlohmann::json none_json_from_str = "none";
    nlohmann::json vertical_json_from_enum = vortex::turb::legacy::settings::GravityMode::Vertical;
    nlohmann::json vertical_json_from_str = "vertical";
    nlohmann::json horizontal_json_from_enum = vortex::turb::legacy::settings::GravityMode::Horizontal;
    nlohmann::json horizontal_json_from_str = "horizontal";
    nlohmann::json invalid_json_from_str = "unknown";

    REQUIRE( none_json_from_enum == "none" );
    REQUIRE( none_json_from_str == "none" );
    REQUIRE( vertical_json_from_enum == "vertical" );
    REQUIRE( vertical_json_from_str == "vertical" );
    REQUIRE( horizontal_json_from_enum == "horizontal" );
    REQUIRE( horizontal_json_from_str == "horizontal" );
    REQUIRE( invalid_json_from_str == "unknown" );

    REQUIRE( none_json_from_enum.template get< vortex::turb::legacy::settings::GravityMode >() == vortex::turb::legacy::settings::GravityMode::None );
    REQUIRE( none_json_from_str.template get< vortex::turb::legacy::settings::GravityMode >() == vortex::turb::legacy::settings::GravityMode::None );
    REQUIRE( vertical_json_from_enum.template get< vortex::turb::legacy::settings::GravityMode >() == vortex::turb::legacy::settings::GravityMode::Vertical );
    REQUIRE( vertical_json_from_str.template get< vortex::turb::legacy::settings::GravityMode >() == vortex::turb::legacy::settings::GravityMode::Vertical );
    REQUIRE( horizontal_json_from_enum.template get< vortex::turb::legacy::settings::GravityMode >() == vortex::turb::legacy::settings::GravityMode::Horizontal );
    REQUIRE( horizontal_json_from_str.template get< vortex::turb::legacy::settings::GravityMode >() == vortex::turb::legacy::settings::GravityMode::Horizontal );
    REQUIRE( invalid_json_from_str.template get< vortex::turb::legacy::settings::GravityMode >() == vortex::turb::legacy::settings::GravityMode::None );
}
