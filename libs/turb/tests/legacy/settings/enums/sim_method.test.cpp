// 
// Unit test source file auto-generated by VORTEX SETTINGS WIZARD
// 
// TODO: Just testing
// 

#include <cstring>
#include <string>
#include <catch2/catch_test_macros.hpp>
#include <nlohmann/json.hpp>
#include "turb/legacy/settings/enums/sim_method.hpp"
#include "turb/legacy/settings/enums/sim_method_json_integration.hpp"

TEST_CASE( "SimMethod - conversion between enums and strings", "[sample]" )
{
    using namespace std::string_literals;

    // Testing conversions for SimMethod::Dns
    REQUIRE( vortex::turb::legacy::settings::to_string( vortex::turb::legacy::settings::SimMethod::Dns ) == "dns"s );
    REQUIRE( std::strcmp( vortex::turb::legacy::settings::to_c_str( vortex::turb::legacy::settings::SimMethod::Dns ), "dns" ) == 0 );
    REQUIRE( vortex::turb::legacy::settings::to_sim_method( "dns" ) == vortex::turb::legacy::settings::SimMethod::Dns );
    REQUIRE( vortex::turb::legacy::settings::to_sim_method( "dns"s ) == vortex::turb::legacy::settings::SimMethod::Dns );
    REQUIRE( vortex::turb::legacy::settings::to_sim_method( vortex::turb::legacy::settings::to_string( vortex::turb::legacy::settings::SimMethod::Dns ) ) == vortex::turb::legacy::settings::SimMethod::Dns );
    REQUIRE( vortex::turb::legacy::settings::to_sim_method( vortex::turb::legacy::settings::to_c_str( vortex::turb::legacy::settings::SimMethod::Dns ) ) == vortex::turb::legacy::settings::SimMethod::Dns );

    // Testing conversions for SimMethod::Les
    REQUIRE( vortex::turb::legacy::settings::to_string( vortex::turb::legacy::settings::SimMethod::Les ) == "les"s );
    REQUIRE( std::strcmp( vortex::turb::legacy::settings::to_c_str( vortex::turb::legacy::settings::SimMethod::Les ), "les" ) == 0 );
    REQUIRE( vortex::turb::legacy::settings::to_sim_method( "les" ) == vortex::turb::legacy::settings::SimMethod::Les );
    REQUIRE( vortex::turb::legacy::settings::to_sim_method( "les"s ) == vortex::turb::legacy::settings::SimMethod::Les );
    REQUIRE( vortex::turb::legacy::settings::to_sim_method( vortex::turb::legacy::settings::to_string( vortex::turb::legacy::settings::SimMethod::Les ) ) == vortex::turb::legacy::settings::SimMethod::Les );
    REQUIRE( vortex::turb::legacy::settings::to_sim_method( vortex::turb::legacy::settings::to_c_str( vortex::turb::legacy::settings::SimMethod::Les ) ) == vortex::turb::legacy::settings::SimMethod::Les );

    // Testing conversions for SimMethod::Fdns
    REQUIRE( vortex::turb::legacy::settings::to_string( vortex::turb::legacy::settings::SimMethod::Fdns ) == "fdns"s );
    REQUIRE( std::strcmp( vortex::turb::legacy::settings::to_c_str( vortex::turb::legacy::settings::SimMethod::Fdns ), "fdns" ) == 0 );
    REQUIRE( vortex::turb::legacy::settings::to_sim_method( "fdns" ) == vortex::turb::legacy::settings::SimMethod::Fdns );
    REQUIRE( vortex::turb::legacy::settings::to_sim_method( "fdns"s ) == vortex::turb::legacy::settings::SimMethod::Fdns );
    REQUIRE( vortex::turb::legacy::settings::to_sim_method( vortex::turb::legacy::settings::to_string( vortex::turb::legacy::settings::SimMethod::Fdns ) ) == vortex::turb::legacy::settings::SimMethod::Fdns );
    REQUIRE( vortex::turb::legacy::settings::to_sim_method( vortex::turb::legacy::settings::to_c_str( vortex::turb::legacy::settings::SimMethod::Fdns ) ) == vortex::turb::legacy::settings::SimMethod::Fdns );

    // Testing conversions for values out of range
    REQUIRE( vortex::turb::legacy::settings::to_string( static_cast< vortex::turb::legacy::settings::SimMethod >( 3 ) ) == "unknown"s );
    REQUIRE( std::strcmp( vortex::turb::legacy::settings::to_c_str( static_cast< vortex::turb::legacy::settings::SimMethod >( 3 ) ), "unknown" ) == 0 );
    REQUIRE( vortex::turb::legacy::settings::to_sim_method( "" ) == vortex::turb::legacy::settings::SimMethod::Dns );
    REQUIRE( vortex::turb::legacy::settings::to_sim_method( ""s ) == vortex::turb::legacy::settings::SimMethod::Dns );
}


TEST_CASE( "SimMethod - integration with json serialization", "[sample]" )
{
    nlohmann::json dns_json_from_enum = vortex::turb::legacy::settings::SimMethod::Dns;
    nlohmann::json dns_json_from_str = "dns";
    nlohmann::json les_json_from_enum = vortex::turb::legacy::settings::SimMethod::Les;
    nlohmann::json les_json_from_str = "les";
    nlohmann::json fdns_json_from_enum = vortex::turb::legacy::settings::SimMethod::Fdns;
    nlohmann::json fdns_json_from_str = "fdns";
    nlohmann::json invalid_json_from_str = "unknown";

    REQUIRE( dns_json_from_enum == "dns" );
    REQUIRE( dns_json_from_str == "dns" );
    REQUIRE( les_json_from_enum == "les" );
    REQUIRE( les_json_from_str == "les" );
    REQUIRE( fdns_json_from_enum == "fdns" );
    REQUIRE( fdns_json_from_str == "fdns" );
    REQUIRE( invalid_json_from_str == "unknown" );

    REQUIRE( dns_json_from_enum.template get< vortex::turb::legacy::settings::SimMethod >() == vortex::turb::legacy::settings::SimMethod::Dns );
    REQUIRE( dns_json_from_str.template get< vortex::turb::legacy::settings::SimMethod >() == vortex::turb::legacy::settings::SimMethod::Dns );
    REQUIRE( les_json_from_enum.template get< vortex::turb::legacy::settings::SimMethod >() == vortex::turb::legacy::settings::SimMethod::Les );
    REQUIRE( les_json_from_str.template get< vortex::turb::legacy::settings::SimMethod >() == vortex::turb::legacy::settings::SimMethod::Les );
    REQUIRE( fdns_json_from_enum.template get< vortex::turb::legacy::settings::SimMethod >() == vortex::turb::legacy::settings::SimMethod::Fdns );
    REQUIRE( fdns_json_from_str.template get< vortex::turb::legacy::settings::SimMethod >() == vortex::turb::legacy::settings::SimMethod::Fdns );
    REQUIRE( invalid_json_from_str.template get< vortex::turb::legacy::settings::SimMethod >() == vortex::turb::legacy::settings::SimMethod::Dns );
}
