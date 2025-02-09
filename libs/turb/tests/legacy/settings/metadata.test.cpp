// 
// Unit test source file auto-generated by VORTEX SETTINGS WIZARD
// 
// TODO: Just testing
// 

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <nlohmann/json.hpp>

#include "turb/legacy/settings/metadata.hpp"

TEST_CASE( "Metadata - basic test", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };

    REQUIRE( !s.is_empty() );

    auto data_p = s.data();
    auto anys = s.as_any();

    REQUIRE( !anys.is_empty() );

    auto ss = vortex::turb::legacy::settings::Metadata{ anys };

    REQUIRE( !ss.is_empty() );
    REQUIRE( data_p != nullptr );
    REQUIRE( obj == *data_p );
    REQUIRE( *anys.data() == *data_p );
    REQUIRE( *ss.data() == *data_p );
}

TEST_CASE( "Metadata - basic empty test", "[settings]" )
{
    auto s = vortex::turb::legacy::settings::Metadata{};

    REQUIRE( s.is_empty() );

    auto anys = s.as_any();

    REQUIRE( anys.is_empty() );

    auto ss = vortex::turb::legacy::settings::Metadata{ anys };

    REQUIRE( ss.is_empty() );
    REQUIRE( s.data() == nullptr );
    REQUIRE( anys.data() == nullptr );
    REQUIRE( ss.data() == nullptr );
}

TEST_CASE( "Metadata - conversion to string", "[settings][.][!mayfail]" )
{
    // TODO - add conversion to string tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "Metadata - conversion to string - display all", "[settings][.][!mayfail]" )
{
    // TODO - add conversion to string tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "Metadata - conversion to string - extra indent size", "[settings][.][!mayfail]" )
{
    // TODO - add conversion to string tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "Metadata - conversion to string - extra indent level", "[settings][.][!mayfail]" )
{
    // TODO - add conversion to string tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "Metadata - conversion to string for empty", "[settings][.][!mayfail]" )
{
    // TODO - add conversion to string tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "Metadata - merge", "[settings][.][!mayfail]" )
{
    // TODO - add merge tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "Metadata - merge with removal", "[settings][.][!mayfail]" )
{
    // TODO - add merge tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "Metadata - merge with empties", "[settings][.][!mayfail]" )
{
    // TODO - add merge tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "Metadata - equality and inequality operators", "[settings][.][!mayfail]" )
{
    // TODO - add merge tests for generated setting classes
    REQUIRE( false );
}

// "sim_method" property

TEST_CASE( "Metadata - property: \"sim_method\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "sim_method", "fdns" } };
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    auto value = s.sim_method();
    auto default_value = s_null.sim_method();

    REQUIRE( value == vortex::turb::legacy::settings::SimMethod::Fdns );
    REQUIRE( default_value == vortex::turb::legacy::settings::SimMethod::Dns );

    REQUIRE( s.has_sim_method_set() );
    REQUIRE( !s_null.has_sim_method_set() );
}

TEST_CASE( "Metadata - property: \"sim_method\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    const auto value = vortex::turb::legacy::settings::SimMethod::Fdns;

    REQUIRE( !s.has_sim_method_set() );
    REQUIRE( !s_null.has_sim_method_set() );

    REQUIRE_NOTHROW( s.reset_sim_method() );
    REQUIRE_NOTHROW( s_null.reset_sim_method() );

    REQUIRE_THROWS_AS( s_null.set_sim_method( value ), std::runtime_error );

    s.set_sim_method( value );
    REQUIRE( s.has_sim_method_set() );
    REQUIRE( s.sim_method() == value );

    s.reset_sim_method();
    REQUIRE( !s.has_sim_method_set() );

}

// "particle_mode" property

TEST_CASE( "Metadata - property: \"particle_mode\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "particle_mode", "twc" } };
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    auto value = s.particle_mode();
    auto default_value = s_null.particle_mode();

    REQUIRE( value == vortex::turb::legacy::settings::ParticleMode::Twc );
    REQUIRE( default_value == vortex::turb::legacy::settings::ParticleMode::None );

    REQUIRE( s.has_particle_mode_set() );
    REQUIRE( !s_null.has_particle_mode_set() );
}

TEST_CASE( "Metadata - property: \"particle_mode\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    const auto value = vortex::turb::legacy::settings::ParticleMode::Twc;

    REQUIRE( !s.has_particle_mode_set() );
    REQUIRE( !s_null.has_particle_mode_set() );

    REQUIRE_NOTHROW( s.reset_particle_mode() );
    REQUIRE_NOTHROW( s_null.reset_particle_mode() );

    REQUIRE_THROWS_AS( s_null.set_particle_mode( value ), std::runtime_error );

    s.set_particle_mode( value );
    REQUIRE( s.has_particle_mode_set() );
    REQUIRE( s.particle_mode() == value );

    s.reset_particle_mode();
    REQUIRE( !s.has_particle_mode_set() );

}

// "gravity_type" property

TEST_CASE( "Metadata - property: \"gravity_type\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "gravity_type", "horizontal" } };
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    auto value = s.gravity_type();
    auto default_value = s_null.gravity_type();

    REQUIRE( value == vortex::turb::legacy::settings::GravityMode::Horizontal );
    REQUIRE( default_value == vortex::turb::legacy::settings::GravityMode::None );

    REQUIRE( s.has_gravity_type_set() );
    REQUIRE( !s_null.has_gravity_type_set() );
}

TEST_CASE( "Metadata - property: \"gravity_type\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    const auto value = vortex::turb::legacy::settings::GravityMode::Horizontal;

    REQUIRE( !s.has_gravity_type_set() );
    REQUIRE( !s_null.has_gravity_type_set() );

    REQUIRE_NOTHROW( s.reset_gravity_type() );
    REQUIRE_NOTHROW( s_null.reset_gravity_type() );

    REQUIRE_THROWS_AS( s_null.set_gravity_type( value ), std::runtime_error );

    s.set_gravity_type( value );
    REQUIRE( s.has_gravity_type_set() );
    REQUIRE( s.gravity_type() == value );

    s.reset_gravity_type();
    REQUIRE( !s.has_gravity_type_set() );

}

// "particle_kernel_type" property

TEST_CASE( "Metadata - property: \"particle_kernel_type\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "particle_kernel_type", "pic" } };
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    auto value = s.particle_kernel_type();
    auto default_value = s_null.particle_kernel_type();

    REQUIRE( value == vortex::turb::legacy::settings::ParticleTwcKernelType::Pic );
    REQUIRE( default_value == vortex::turb::legacy::settings::ParticleTwcKernelType::Pnn );

    REQUIRE( s.has_particle_kernel_type_set() );
    REQUIRE( !s_null.has_particle_kernel_type_set() );
}

TEST_CASE( "Metadata - property: \"particle_kernel_type\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    const auto value = vortex::turb::legacy::settings::ParticleTwcKernelType::Pic;

    REQUIRE( !s.has_particle_kernel_type_set() );
    REQUIRE( !s_null.has_particle_kernel_type_set() );

    REQUIRE_NOTHROW( s.reset_particle_kernel_type() );
    REQUIRE_NOTHROW( s_null.reset_particle_kernel_type() );

    REQUIRE_THROWS_AS( s_null.set_particle_kernel_type( value ), std::runtime_error );

    s.set_particle_kernel_type( value );
    REQUIRE( s.has_particle_kernel_type_set() );
    REQUIRE( s.particle_kernel_type() == value );

    s.reset_particle_kernel_type();
    REQUIRE( !s.has_particle_kernel_type_set() );

}

// "k_filter" property

TEST_CASE( "Metadata - property: \"k_filter\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "k_filter", 8l } };
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    auto value = s.k_filter();
    auto default_value = s_null.k_filter();

    REQUIRE( static_cast< vortex::i32 >( value ) == 8l );
    REQUIRE( static_cast< vortex::i32 >( default_value ) == vortex::i32{} );

    REQUIRE( s.has_k_filter_set() );
    REQUIRE( !s_null.has_k_filter_set() );
}

TEST_CASE( "Metadata - property: \"k_filter\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    const auto value = 8l;

    REQUIRE( !s.has_k_filter_set() );
    REQUIRE( !s_null.has_k_filter_set() );

    REQUIRE_NOTHROW( s.reset_k_filter() );
    REQUIRE_NOTHROW( s_null.reset_k_filter() );

    REQUIRE_THROWS_AS( s_null.set_k_filter( value ), std::runtime_error );

    s.set_k_filter( value );
    REQUIRE( s.has_k_filter_set() );
    REQUIRE( s.k_filter() == value );

    s.reset_k_filter();
    REQUIRE( !s.has_k_filter_set() );

}

// "C_K" property

TEST_CASE( "Metadata - property: \"C_K\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "C_K", 8.3 } };
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    auto value = s.C_K();
    auto default_value = s_null.C_K();

    REQUIRE_THAT( static_cast< vortex::real >( value ), Catch::Matchers::WithinAbs( 8.3, 1e-05 ) );
    REQUIRE_THAT( static_cast< vortex::real >( default_value ), Catch::Matchers::WithinAbs( 2.5, 1e-05 ) );

    REQUIRE( s.has_C_K_set() );
    REQUIRE( !s_null.has_C_K_set() );
}

TEST_CASE( "Metadata - property: \"C_K\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    const auto value = 8.3;

    REQUIRE( !s.has_C_K_set() );
    REQUIRE( !s_null.has_C_K_set() );

    REQUIRE_NOTHROW( s.reset_C_K() );
    REQUIRE_NOTHROW( s_null.reset_C_K() );

    REQUIRE_THROWS_AS( s_null.set_C_K( value ), std::runtime_error );

    s.set_C_K( value );
    REQUIRE( s.has_C_K_set() );
    REQUIRE_THAT( s.C_K(), Catch::Matchers::WithinAbs( value, 1e-05 ) );

    s.reset_C_K();
    REQUIRE( !s.has_C_K_set() );

}

// "target_Phi" property

TEST_CASE( "Metadata - property: \"target_Phi\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "target_Phi", 8.3 } };
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    auto value = s.target_Phi();
    auto default_value = s_null.target_Phi();

    REQUIRE_THAT( static_cast< vortex::real >( value ), Catch::Matchers::WithinAbs( 8.3, 1e-05 ) );
    REQUIRE_THAT( static_cast< vortex::real >( default_value ), Catch::Matchers::WithinAbs( vortex::real{}, 1e-05 ) );

    REQUIRE( s.has_target_Phi_set() );
    REQUIRE( !s_null.has_target_Phi_set() );
}

TEST_CASE( "Metadata - property: \"target_Phi\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    const auto value = 8.3;

    REQUIRE( !s.has_target_Phi_set() );
    REQUIRE( !s_null.has_target_Phi_set() );

    REQUIRE_NOTHROW( s.reset_target_Phi() );
    REQUIRE_NOTHROW( s_null.reset_target_Phi() );

    REQUIRE_THROWS_AS( s_null.set_target_Phi( value ), std::runtime_error );

    s.set_target_Phi( value );
    REQUIRE( s.has_target_Phi_set() );
    REQUIRE_THAT( s.target_Phi(), Catch::Matchers::WithinAbs( value, 1e-05 ) );

    s.reset_target_Phi();
    REQUIRE( !s.has_target_Phi_set() );

}

// "superpart_factor" property

TEST_CASE( "Metadata - property: \"superpart_factor\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "superpart_factor", 8.3 } };
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    auto value = s.superpart_factor();
    auto default_value = s_null.superpart_factor();

    REQUIRE_THAT( static_cast< vortex::real >( value ), Catch::Matchers::WithinAbs( 8.3, 1e-05 ) );
    REQUIRE_THAT( static_cast< vortex::real >( default_value ), Catch::Matchers::WithinAbs( 1.0, 1e-05 ) );

    REQUIRE( s.has_superpart_factor_set() );
    REQUIRE( !s_null.has_superpart_factor_set() );
}

TEST_CASE( "Metadata - property: \"superpart_factor\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    const auto value = 8.3;

    REQUIRE( !s.has_superpart_factor_set() );
    REQUIRE( !s_null.has_superpart_factor_set() );

    REQUIRE_NOTHROW( s.reset_superpart_factor() );
    REQUIRE_NOTHROW( s_null.reset_superpart_factor() );

    REQUIRE_THROWS_AS( s_null.set_superpart_factor( value ), std::runtime_error );

    s.set_superpart_factor( value );
    REQUIRE( s.has_superpart_factor_set() );
    REQUIRE_THAT( s.superpart_factor(), Catch::Matchers::WithinAbs( value, 1e-05 ) );

    s.reset_superpart_factor();
    REQUIRE( !s.has_superpart_factor_set() );

}

// "src_flow_path" property

TEST_CASE( "Metadata - property: \"src_flow_path\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "src_flow_path", "ptest" } };
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    auto value = s.src_flow_path();
    auto default_value = s_null.src_flow_path();

    REQUIRE( value == "ptest" );
    REQUIRE( default_value == "." );

    REQUIRE( s.has_src_flow_path_set() );
    REQUIRE( !s_null.has_src_flow_path_set() );
}

TEST_CASE( "Metadata - property: \"src_flow_path\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    const auto sv = std::string_view{ "sv" };
    const auto str = std::string{ "str" };
    const auto cstr = "cstr";

    REQUIRE( !s.has_src_flow_path_set() );
    REQUIRE( !s_null.has_src_flow_path_set() );

    REQUIRE_NOTHROW( s.reset_src_flow_path() );
    REQUIRE_NOTHROW( s_null.reset_src_flow_path() );

    REQUIRE_THROWS_AS( s_null.set_src_flow_path( sv ), std::runtime_error );
    REQUIRE_THROWS_AS( s_null.set_src_flow_path( str ), std::runtime_error );
    REQUIRE_THROWS_AS( s_null.set_src_flow_path( cstr ), std::runtime_error );
    REQUIRE_THROWS_AS( s_null.set_src_flow_path( std::string{ "mvstr" } ), std::runtime_error );

    s.set_src_flow_path( sv );
    REQUIRE( s.has_src_flow_path_set() );
    REQUIRE( s.src_flow_path() == "sv" );

    s.set_src_flow_path( str );
    REQUIRE( s.has_src_flow_path_set() );
    REQUIRE( s.src_flow_path() == "str" );

    s.set_src_flow_path( cstr );
    REQUIRE( s.has_src_flow_path_set() );
    REQUIRE( s.src_flow_path() == "cstr" );

    s.set_src_flow_path( std::string{ "mvstr" } );
    REQUIRE( s.has_src_flow_path_set() );
    REQUIRE( s.src_flow_path() == "mvstr" );

    s.reset_src_flow_path();
    REQUIRE( !s.has_src_flow_path_set() );

}

// "src_part_path" property

TEST_CASE( "Metadata - property: \"src_part_path\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "src_part_path", "ptest" } };
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    auto value = s.src_part_path();
    auto default_value = s_null.src_part_path();

    REQUIRE( value == "ptest" );
    REQUIRE( default_value == "." );

    REQUIRE( s.has_src_part_path_set() );
    REQUIRE( !s_null.has_src_part_path_set() );
}

TEST_CASE( "Metadata - property: \"src_part_path\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    const auto sv = std::string_view{ "sv" };
    const auto str = std::string{ "str" };
    const auto cstr = "cstr";

    REQUIRE( !s.has_src_part_path_set() );
    REQUIRE( !s_null.has_src_part_path_set() );

    REQUIRE_NOTHROW( s.reset_src_part_path() );
    REQUIRE_NOTHROW( s_null.reset_src_part_path() );

    REQUIRE_THROWS_AS( s_null.set_src_part_path( sv ), std::runtime_error );
    REQUIRE_THROWS_AS( s_null.set_src_part_path( str ), std::runtime_error );
    REQUIRE_THROWS_AS( s_null.set_src_part_path( cstr ), std::runtime_error );
    REQUIRE_THROWS_AS( s_null.set_src_part_path( std::string{ "mvstr" } ), std::runtime_error );

    s.set_src_part_path( sv );
    REQUIRE( s.has_src_part_path_set() );
    REQUIRE( s.src_part_path() == "sv" );

    s.set_src_part_path( str );
    REQUIRE( s.has_src_part_path_set() );
    REQUIRE( s.src_part_path() == "str" );

    s.set_src_part_path( cstr );
    REQUIRE( s.has_src_part_path_set() );
    REQUIRE( s.src_part_path() == "cstr" );

    s.set_src_part_path( std::string{ "mvstr" } );
    REQUIRE( s.has_src_part_path_set() );
    REQUIRE( s.src_part_path() == "mvstr" );

    s.reset_src_part_path();
    REQUIRE( !s.has_src_part_path_set() );

}

// "part_output_delay" property

TEST_CASE( "Metadata - property: \"part_output_delay\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "part_output_delay", 8l } };
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    auto value = s.part_output_delay();
    auto default_value = s_null.part_output_delay();

    REQUIRE( static_cast< vortex::i32 >( value ) == 8l );
    REQUIRE( static_cast< vortex::i32 >( default_value ) == vortex::i32{} );

    REQUIRE( s.has_part_output_delay_set() );
    REQUIRE( !s_null.has_part_output_delay_set() );
}

TEST_CASE( "Metadata - property: \"part_output_delay\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    const auto value = 8l;

    REQUIRE( !s.has_part_output_delay_set() );
    REQUIRE( !s_null.has_part_output_delay_set() );

    REQUIRE_NOTHROW( s.reset_part_output_delay() );
    REQUIRE_NOTHROW( s_null.reset_part_output_delay() );

    REQUIRE_THROWS_AS( s_null.set_part_output_delay( value ), std::runtime_error );

    s.set_part_output_delay( value );
    REQUIRE( s.has_part_output_delay_set() );
    REQUIRE( s.part_output_delay() == value );

    s.reset_part_output_delay();
    REQUIRE( !s.has_part_output_delay_set() );

}

// "is_perf_full_profile_enabled" property

TEST_CASE( "Metadata - property: \"is_perf_full_profile_enabled\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "is_perf_full_profile_enabled", true } };
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    auto value = s.is_perf_full_profile_enabled();
    auto default_value = s_null.is_perf_full_profile_enabled();

    REQUIRE( value == true );
    REQUIRE( default_value == bool{} );

    REQUIRE( s.has_is_perf_full_profile_enabled_set() );
    REQUIRE( !s_null.has_is_perf_full_profile_enabled_set() );
}

TEST_CASE( "Metadata - property: \"is_perf_full_profile_enabled\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    const auto value = true;

    REQUIRE( !s.has_is_perf_full_profile_enabled_set() );
    REQUIRE( !s_null.has_is_perf_full_profile_enabled_set() );

    REQUIRE_NOTHROW( s.reset_is_perf_full_profile_enabled() );
    REQUIRE_NOTHROW( s_null.reset_is_perf_full_profile_enabled() );

    REQUIRE_THROWS_AS( s_null.set_is_perf_full_profile_enabled( value ), std::runtime_error );

    s.set_is_perf_full_profile_enabled( value );
    REQUIRE( s.has_is_perf_full_profile_enabled_set() );
    REQUIRE( s.is_perf_full_profile_enabled() == value );

    s.reset_is_perf_full_profile_enabled();
    REQUIRE( !s.has_is_perf_full_profile_enabled_set() );

}

// "is_perf_simple_enabled" property

TEST_CASE( "Metadata - property: \"is_perf_simple_enabled\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "is_perf_simple_enabled", true } };
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    auto value = s.is_perf_simple_enabled();
    auto default_value = s_null.is_perf_simple_enabled();

    REQUIRE( value == true );
    REQUIRE( default_value == bool{} );

    REQUIRE( s.has_is_perf_simple_enabled_set() );
    REQUIRE( !s_null.has_is_perf_simple_enabled_set() );
}

TEST_CASE( "Metadata - property: \"is_perf_simple_enabled\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    const auto value = true;

    REQUIRE( !s.has_is_perf_simple_enabled_set() );
    REQUIRE( !s_null.has_is_perf_simple_enabled_set() );

    REQUIRE_NOTHROW( s.reset_is_perf_simple_enabled() );
    REQUIRE_NOTHROW( s_null.reset_is_perf_simple_enabled() );

    REQUIRE_THROWS_AS( s_null.set_is_perf_simple_enabled( value ), std::runtime_error );

    s.set_is_perf_simple_enabled( value );
    REQUIRE( s.has_is_perf_simple_enabled_set() );
    REQUIRE( s.is_perf_simple_enabled() == value );

    s.reset_is_perf_simple_enabled();
    REQUIRE( !s.has_is_perf_simple_enabled_set() );

}

// "is_perf_part_dist_enabled" property

TEST_CASE( "Metadata - property: \"is_perf_part_dist_enabled\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "is_perf_part_dist_enabled", true } };
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    auto value = s.is_perf_part_dist_enabled();
    auto default_value = s_null.is_perf_part_dist_enabled();

    REQUIRE( value == true );
    REQUIRE( default_value == bool{} );

    REQUIRE( s.has_is_perf_part_dist_enabled_set() );
    REQUIRE( !s_null.has_is_perf_part_dist_enabled_set() );
}

TEST_CASE( "Metadata - property: \"is_perf_part_dist_enabled\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    const auto value = true;

    REQUIRE( !s.has_is_perf_part_dist_enabled_set() );
    REQUIRE( !s_null.has_is_perf_part_dist_enabled_set() );

    REQUIRE_NOTHROW( s.reset_is_perf_part_dist_enabled() );
    REQUIRE_NOTHROW( s_null.reset_is_perf_part_dist_enabled() );

    REQUIRE_THROWS_AS( s_null.set_is_perf_part_dist_enabled( value ), std::runtime_error );

    s.set_is_perf_part_dist_enabled( value );
    REQUIRE( s.has_is_perf_part_dist_enabled_set() );
    REQUIRE( s.is_perf_part_dist_enabled() == value );

    s.reset_is_perf_part_dist_enabled();
    REQUIRE( !s.has_is_perf_part_dist_enabled_set() );

}

// "perf_full_start" property

TEST_CASE( "Metadata - property: \"perf_full_start\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "perf_full_start", 8l } };
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    auto value = s.perf_full_start();
    auto default_value = s_null.perf_full_start();

    REQUIRE( static_cast< vortex::i32 >( value ) == 8l );
    REQUIRE( static_cast< vortex::i32 >( default_value ) == vortex::i32{} );

    REQUIRE( s.has_perf_full_start_set() );
    REQUIRE( !s_null.has_perf_full_start_set() );
}

TEST_CASE( "Metadata - property: \"perf_full_start\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    const auto value = 8l;

    REQUIRE( !s.has_perf_full_start_set() );
    REQUIRE( !s_null.has_perf_full_start_set() );

    REQUIRE_NOTHROW( s.reset_perf_full_start() );
    REQUIRE_NOTHROW( s_null.reset_perf_full_start() );

    REQUIRE_THROWS_AS( s_null.set_perf_full_start( value ), std::runtime_error );

    s.set_perf_full_start( value );
    REQUIRE( s.has_perf_full_start_set() );
    REQUIRE( s.perf_full_start() == value );

    s.reset_perf_full_start();
    REQUIRE( !s.has_perf_full_start_set() );

}

// "perf_full_end" property

TEST_CASE( "Metadata - property: \"perf_full_end\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "perf_full_end", 8l } };
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    auto value = s.perf_full_end();
    auto default_value = s_null.perf_full_end();

    REQUIRE( static_cast< vortex::i32 >( value ) == 8l );
    REQUIRE( static_cast< vortex::i32 >( default_value ) == vortex::i32{} );

    REQUIRE( s.has_perf_full_end_set() );
    REQUIRE( !s_null.has_perf_full_end_set() );
}

TEST_CASE( "Metadata - property: \"perf_full_end\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    const auto value = 8l;

    REQUIRE( !s.has_perf_full_end_set() );
    REQUIRE( !s_null.has_perf_full_end_set() );

    REQUIRE_NOTHROW( s.reset_perf_full_end() );
    REQUIRE_NOTHROW( s_null.reset_perf_full_end() );

    REQUIRE_THROWS_AS( s_null.set_perf_full_end( value ), std::runtime_error );

    s.set_perf_full_end( value );
    REQUIRE( s.has_perf_full_end_set() );
    REQUIRE( s.perf_full_end() == value );

    s.reset_perf_full_end();
    REQUIRE( !s.has_perf_full_end_set() );

}

// "part_perf_interval" property

TEST_CASE( "Metadata - property: \"part_perf_interval\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "part_perf_interval", 8l } };
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    auto value = s.part_perf_interval();
    auto default_value = s_null.part_perf_interval();

    REQUIRE( static_cast< vortex::i32 >( value ) == 8l );
    REQUIRE( static_cast< vortex::i32 >( default_value ) == vortex::i32{} );

    REQUIRE( s.has_part_perf_interval_set() );
    REQUIRE( !s_null.has_part_perf_interval_set() );
}

TEST_CASE( "Metadata - property: \"part_perf_interval\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::turb::legacy::settings::Metadata{ &obj };
    auto s_null = vortex::turb::legacy::settings::Metadata{};

    const auto value = 8l;

    REQUIRE( !s.has_part_perf_interval_set() );
    REQUIRE( !s_null.has_part_perf_interval_set() );

    REQUIRE_NOTHROW( s.reset_part_perf_interval() );
    REQUIRE_NOTHROW( s_null.reset_part_perf_interval() );

    REQUIRE_THROWS_AS( s_null.set_part_perf_interval( value ), std::runtime_error );

    s.set_part_perf_interval( value );
    REQUIRE( s.has_part_perf_interval_set() );
    REQUIRE( s.part_perf_interval() == value );

    s.reset_part_perf_interval();
    REQUIRE( !s.has_part_perf_interval_set() );

}


