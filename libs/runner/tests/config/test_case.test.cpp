// 
// Unit test source file auto-generated by VORTEX SETTINGS WIZARD
// 
// TODO: Just testing
// 

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <nlohmann/json.hpp>

#include "runner/config/test_case.hpp"

TEST_CASE( "TestCase - basic test", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::runner::config::TestCase{ &obj };

    REQUIRE( !s.is_empty() );

    auto data_p = s.data();
    auto anys = s.as_any();

    REQUIRE( !anys.is_empty() );

    auto ss = vortex::runner::config::TestCase{ anys };

    REQUIRE( !ss.is_empty() );
    REQUIRE( data_p != nullptr );
    REQUIRE( obj == *data_p );
    REQUIRE( *anys.data() == *data_p );
    REQUIRE( *ss.data() == *data_p );
}

TEST_CASE( "TestCase - basic empty test", "[settings]" )
{
    auto s = vortex::runner::config::TestCase{};

    REQUIRE( s.is_empty() );

    auto anys = s.as_any();

    REQUIRE( anys.is_empty() );

    auto ss = vortex::runner::config::TestCase{ anys };

    REQUIRE( ss.is_empty() );
    REQUIRE( s.data() == nullptr );
    REQUIRE( anys.data() == nullptr );
    REQUIRE( ss.data() == nullptr );
}

TEST_CASE( "TestCase - conversion to string", "[settings][.][!mayfail]" )
{
    // TODO - add conversion to string tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "TestCase - conversion to string - display all", "[settings][.][!mayfail]" )
{
    // TODO - add conversion to string tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "TestCase - conversion to string - extra indent size", "[settings][.][!mayfail]" )
{
    // TODO - add conversion to string tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "TestCase - conversion to string - extra indent level", "[settings][.][!mayfail]" )
{
    // TODO - add conversion to string tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "TestCase - conversion to string for empty", "[settings][.][!mayfail]" )
{
    // TODO - add conversion to string tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "TestCase - merge", "[settings][.][!mayfail]" )
{
    // TODO - add merge tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "TestCase - merge with removal", "[settings][.][!mayfail]" )
{
    // TODO - add merge tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "TestCase - merge with empties", "[settings][.][!mayfail]" )
{
    // TODO - add merge tests for generated setting classes
    REQUIRE( false );
}

TEST_CASE( "TestCase - equality and inequality operators", "[settings][.][!mayfail]" )
{
    // TODO - add merge tests for generated setting classes
    REQUIRE( false );
}

// "name" property

TEST_CASE( "TestCase - property: \"name\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "name", "stest" } };
    auto s = vortex::runner::config::TestCase{ &obj };
    auto s_null = vortex::runner::config::TestCase{};

    auto value = s.name();
    auto default_value = s_null.name();

    REQUIRE( value == "stest" );
    REQUIRE( default_value == std::string_view{} );

    REQUIRE( s.has_name_set() );
    REQUIRE( !s_null.has_name_set() );
}

TEST_CASE( "TestCase - property: \"name\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::runner::config::TestCase{ &obj };
    auto s_null = vortex::runner::config::TestCase{};

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

// "template_name" property

TEST_CASE( "TestCase - property: \"template_name\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "template_name", "stest" } };
    auto s = vortex::runner::config::TestCase{ &obj };
    auto s_null = vortex::runner::config::TestCase{};

    auto value = s.template_name();
    auto default_value = s_null.template_name();

    REQUIRE( value == "stest" );
    REQUIRE( default_value == std::string_view{} );

    REQUIRE( s.has_template_name_set() );
    REQUIRE( !s_null.has_template_name_set() );
}

TEST_CASE( "TestCase - property: \"template_name\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::runner::config::TestCase{ &obj };
    auto s_null = vortex::runner::config::TestCase{};

    const auto sv = std::string_view{ "sv" };
    const auto str = std::string{ "str" };
    const auto cstr = "cstr";

    REQUIRE( !s.has_template_name_set() );
    REQUIRE( !s_null.has_template_name_set() );

    REQUIRE_NOTHROW( s.reset_template_name() );
    REQUIRE_NOTHROW( s_null.reset_template_name() );

    REQUIRE_THROWS_AS( s_null.set_template_name( sv ), std::runtime_error );
    REQUIRE_THROWS_AS( s_null.set_template_name( str ), std::runtime_error );
    REQUIRE_THROWS_AS( s_null.set_template_name( cstr ), std::runtime_error );
    REQUIRE_THROWS_AS( s_null.set_template_name( std::string{ "mvstr" } ), std::runtime_error );

    s.set_template_name( sv );
    REQUIRE( s.has_template_name_set() );
    REQUIRE( s.template_name() == "sv" );

    s.set_template_name( str );
    REQUIRE( s.has_template_name_set() );
    REQUIRE( s.template_name() == "str" );

    s.set_template_name( cstr );
    REQUIRE( s.has_template_name_set() );
    REQUIRE( s.template_name() == "cstr" );

    s.set_template_name( std::string{ "mvstr" } );
    REQUIRE( s.has_template_name_set() );
    REQUIRE( s.template_name() == "mvstr" );

    s.reset_template_name();
    REQUIRE( !s.has_template_name_set() );

}

// "settings" property

TEST_CASE( "TestCase - property: \"settings\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "settings", { { "x", "y"} } } };
    auto s = vortex::runner::config::TestCase{ &obj };
    auto s_null = vortex::runner::config::TestCase{};

    auto value = s.settings();
    auto default_value = s_null.settings();

    REQUIRE( !value.is_empty() );
    REQUIRE( value.data()->at( "x" ) == "y" );
    REQUIRE( default_value.is_empty() );

    REQUIRE( s.has_settings_set() );
    REQUIRE( !s_null.has_settings_set() );
}

TEST_CASE( "TestCase - property: \"settings\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::runner::config::TestCase{ &obj };
    auto s_null = vortex::runner::config::TestCase{};

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

// "parallel_strategy" property

TEST_CASE( "TestCase - property: \"parallel_strategy\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "parallel_strategy", "xxx" } };
    auto s = vortex::runner::config::TestCase{ &obj };
    auto s_null = vortex::runner::config::TestCase{};

    auto value = s.parallel_strategy();
    auto default_value = s_null.parallel_strategy();

    REQUIRE( value == vortex::runner::config::ParallelStrategyType::Xxx );
    REQUIRE( default_value == vortex::runner::config::ParallelStrategyType::Mmx );

    REQUIRE( s.has_parallel_strategy_set() );
    REQUIRE( !s_null.has_parallel_strategy_set() );
}

TEST_CASE( "TestCase - property: \"parallel_strategy\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::runner::config::TestCase{ &obj };
    auto s_null = vortex::runner::config::TestCase{};

    const auto value = vortex::runner::config::ParallelStrategyType::Xxx;

    REQUIRE( !s.has_parallel_strategy_set() );
    REQUIRE( !s_null.has_parallel_strategy_set() );

    REQUIRE_NOTHROW( s.reset_parallel_strategy() );
    REQUIRE_NOTHROW( s_null.reset_parallel_strategy() );

    REQUIRE_THROWS_AS( s_null.set_parallel_strategy( value ), std::runtime_error );

    s.set_parallel_strategy( value );
    REQUIRE( s.has_parallel_strategy_set() );
    REQUIRE( s.parallel_strategy() == value );

    s.reset_parallel_strategy();
    REQUIRE( !s.has_parallel_strategy_set() );

}

// "stages" property

TEST_CASE( "TestCase - property: \"stages\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "stages", { "stest", "stest", "stest" } } };
    auto s = vortex::runner::config::TestCase{ &obj };
    auto s_null = vortex::runner::config::TestCase{};

    auto value = s.stages();
    auto default_value = s_null.stages();

    REQUIRE( value.size() == 3ull );
    REQUIRE( value[ 0 ] == "stest" );
    REQUIRE( value[ 1 ] == "stest" );
    REQUIRE( value[ 2 ] == "stest" );
    REQUIRE( default_value.empty() );

    REQUIRE( s.has_stages_set() );
    REQUIRE( !s_null.has_stages_set() );
}

TEST_CASE( "TestCase - property: \"stages\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::runner::config::TestCase{ &obj };
    auto s_null = vortex::runner::config::TestCase{};

    const auto value = std::vector< std::string >{ "stest", "stest", "stest" };

    REQUIRE( !s.has_stages_set() );
    REQUIRE( !s_null.has_stages_set() );

    REQUIRE_NOTHROW( s.reset_stages() );
    REQUIRE_NOTHROW( s_null.reset_stages() );

    REQUIRE_THROWS_AS( s_null.set_stages( value ), std::runtime_error );
    REQUIRE_THROWS_AS( s_null.set_stages( std::vector< std::string >{ value } ), std::runtime_error );
    REQUIRE_THROWS_AS( s_null.set_stages( { "stest", "stest", "stest" } ), std::runtime_error );

    s.reset_stages();
    REQUIRE( !s.has_stages_set() );

    s.set_stages( value );
    REQUIRE( s.has_stages_set() );
    REQUIRE( s.stages() == value );

    s.reset_stages();
    REQUIRE( !s.has_stages_set() );

    s.set_stages( std::vector< std::string >{ value } );
    REQUIRE( s.has_stages_set() );
    REQUIRE( s.stages() == value );

    s.reset_stages();
    REQUIRE( !s.has_stages_set() );

    s.set_stages( { "stest", "stest", "stest" } );
    REQUIRE( s.has_stages_set() );
    REQUIRE( s.stages() == value );

    s.reset_stages();
    REQUIRE( !s.has_stages_set() );

}

TEST_CASE( "TestCase - property: \"stages\" - array-specific - empty object", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::runner::config::TestCase{ &obj };

    const auto value = std::string{ "str" };
    const auto xvalue = std::string{ "xstr" };
    const auto sv = std::string_view{ "sv" };
    const auto cstr = "cstr";

    REQUIRE( !s.has_stages_set() );

    s.clear_stages();

    REQUIRE( s.has_stages_set() );
    REQUIRE( s.are_stages_empty() );
    REQUIRE( s.stages_count() == 0ull );

    s.reset_stages();
    REQUIRE( !s.has_stages_set() );

    s.add_stage( value );

    REQUIRE( s.has_stages_set() );
    REQUIRE( !s.are_stages_empty() );
    REQUIRE( s.stages_count() == 1ull );
    REQUIRE( s.stage_at( 0 ) == value );

    s.add_stage( xvalue );

    REQUIRE( s.has_stages_set() );
    REQUIRE( !s.are_stages_empty() );
    REQUIRE( s.stages_count() == 2ull );
    REQUIRE( s.stage_at( 0 ) == value );
    REQUIRE( s.stage_at( 1 ) == xvalue );

    s.remove_stage( value );

    REQUIRE( s.has_stages_set() );
    REQUIRE( !s.are_stages_empty() );
    REQUIRE( s.stages_count() == 1ull );
    REQUIRE( s.stage_at( 0 ) == xvalue );

    s.add_stage( value );

    REQUIRE( s.has_stages_set() );
    REQUIRE( !s.are_stages_empty() );
    REQUIRE( s.stages_count() == 2ull );
    REQUIRE( s.stage_at( 0 ) == xvalue );
    REQUIRE( s.stage_at( 1 ) == value );

    s.remove_stage_at( 0 );

    REQUIRE( s.has_stages_set() );
    REQUIRE( !s.are_stages_empty() );
    REQUIRE( s.stages_count() == 1ull );
    REQUIRE( s.stage_at( 0 ) == value );

    s.remove_stage( xvalue );

    REQUIRE( s.has_stages_set() );
    REQUIRE( !s.are_stages_empty() );
    REQUIRE( s.stages_count() == 1ull );
    REQUIRE( s.stage_at( 0 ) == value );

    s.clear_stages();

    REQUIRE( s.has_stages_set() );
    REQUIRE( s.are_stages_empty() );
    REQUIRE( s.stages_count() == 0ull );

    REQUIRE_THROWS_AS( s.stage_at( 0 ), nlohmann::json::out_of_range );
    REQUIRE_THROWS_AS( s.remove_stage_at( 0 ), nlohmann::json::out_of_range );
    REQUIRE_NOTHROW( s.clear_stages() );
    REQUIRE_NOTHROW( s.remove_stage( value ) );

    s.add_stage( value );
    REQUIRE( s.stages_count() == 1ull );
    REQUIRE( s.stage_at( 0 ) == value );

    s.add_stage( std::string{ xvalue } );
    REQUIRE( s.stages_count() == 2ull );
    REQUIRE( s.stage_at( 1 ) == xvalue );

    s.add_stage( sv );
    REQUIRE( s.stages_count() == 3ull );
    REQUIRE( s.stage_at( 2 ) == sv );

    s.add_stage( cstr );
    REQUIRE( s.stages_count() == 4ull );
    REQUIRE( s.stage_at( 3 ) == cstr );

    s.remove_stage( value );
    REQUIRE( s.stages_count() == 3ull );
    REQUIRE( s.stage_at( 0 ) == xvalue );

    s.remove_stage( std::string{ xvalue } );
    REQUIRE( s.stages_count() == 2ull );
    REQUIRE( s.stage_at( 0 ) == sv );

    s.remove_stage( sv );
    REQUIRE( s.stages_count() == 1ull );
    REQUIRE( s.stage_at( 0 ) == cstr );

    s.remove_stage( cstr );
    REQUIRE( s.stages_count() == 0ull );
}

TEST_CASE( "TestCase - property: \"stages\" - array-specific", "[settings]" )
{
    auto s_null = vortex::runner::config::TestCase{};
    const auto sv = std::string_view{ "sv" };
    const auto str = std::string{ "str" };
    const auto cstr = "cstr";

    REQUIRE( s_null.are_stages_empty() );
    REQUIRE( s_null.stages_count() == 0ull );

    REQUIRE_THROWS_AS( s_null.stage_at( 0ull ), std::runtime_error );
    REQUIRE_NOTHROW( s_null.clear_stages() );
    REQUIRE_NOTHROW( s_null.remove_stage_at( 0ull ) );

    REQUIRE_THROWS_AS( s_null.add_stage( sv ), std::runtime_error );
    REQUIRE_THROWS_AS( s_null.add_stage( str ), std::runtime_error );
    REQUIRE_THROWS_AS( s_null.add_stage( cstr ), std::runtime_error );
    REQUIRE_THROWS_AS( s_null.add_stage( std::string{ str } ), std::runtime_error );

    REQUIRE_NOTHROW( s_null.remove_stage( sv ) );
    REQUIRE_NOTHROW( s_null.remove_stage( str ) );
    REQUIRE_NOTHROW( s_null.remove_stage( cstr ) );
    REQUIRE_NOTHROW( s_null.remove_stage( std::string{ str } ) );
}

// "process_count" property

TEST_CASE( "TestCase - property: \"process_count\" - getter, default, has_set", "[settings]" )
{
    nlohmann::json obj = { { "process_count", -2l } };
    auto s = vortex::runner::config::TestCase{ &obj };
    auto s_null = vortex::runner::config::TestCase{};

    auto value = s.process_count();
    auto default_value = s_null.process_count();

    REQUIRE( static_cast< vortex::i32 >( value ) == -2l );
    REQUIRE( static_cast< vortex::i32 >( default_value ) == 1 );

    REQUIRE( s.has_process_count_set() );
    REQUIRE( !s_null.has_process_count_set() );
}

TEST_CASE( "TestCase - property: \"process_count\" - setter, reset", "[settings]" )
{
    nlohmann::json obj = nlohmann::json::object();
    auto s = vortex::runner::config::TestCase{ &obj };
    auto s_null = vortex::runner::config::TestCase{};

    const auto value = -2l;

    REQUIRE( !s.has_process_count_set() );
    REQUIRE( !s_null.has_process_count_set() );

    REQUIRE_NOTHROW( s.reset_process_count() );
    REQUIRE_NOTHROW( s_null.reset_process_count() );

    REQUIRE_THROWS_AS( s_null.set_process_count( value ), std::runtime_error );

    s.set_process_count( value );
    REQUIRE( s.has_process_count_set() );
    REQUIRE( s.process_count() == value );

    s.reset_process_count();
    REQUIRE( !s.has_process_count_set() );

}


