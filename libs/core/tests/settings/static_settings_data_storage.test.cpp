#include <catch2/catch_test_macros.hpp>

#include <exception>
#include <cstring>

#include "core/settings/static_settings_data_storage.hpp"

TEST_CASE("Static Settings Data Storage - basic allocation", "[settings]")
{
    auto ds = vortex::core::settings::StaticSettingsDataStorage{};

    REQUIRE_NOTHROW( ds.allocate( 16ull ) );
    REQUIRE_NOTHROW( ds.allocate( 0ull ) );

    auto data_p = ds.allocate( 32ull );

    REQUIRE( data_p != nullptr );
}

TEST_CASE("Static Settings Data Storage - basic deallocation", "[settings]")
{
    auto ds = vortex::core::settings::StaticSettingsDataStorage{};
    auto data_p = ds.allocate( 128ull );

    REQUIRE_NOTHROW( ds.deallocate( data_p ) );
}

TEST_CASE("Static Settings Data Storage - missed or double deallocation", "[settings]")
{
    auto ds = vortex::core::settings::StaticSettingsDataStorage{};
    auto data_p = ds.allocate( 256ull );

    REQUIRE_NOTHROW( ds.deallocate( data_p ) );
    REQUIRE_NOTHROW( ds.deallocate( data_p ) );
    REQUIRE_NOTHROW( ds.deallocate( reinterpret_cast< void * >( 123ull ) ) );
}

TEST_CASE("Static Settings Data Storage - storing string test", "[settings]")
{
    auto ds = vortex::core::settings::StaticSettingsDataStorage{};
    auto test_string = "test";

    auto data_p = ds.allocate( 5ull );
    std::memcpy( data_p, &test_string[ 0 ], 5ull );

    REQUIRE( std::strcmp( static_cast< char * >( data_p ), "test" ) == 0 );
}

TEST_CASE("Static Settings Data Storage - storing array test", "[settings]")
{
    auto ds = vortex::core::settings::StaticSettingsDataStorage{};
    int test_array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    auto size = 10ull * sizeof( int );
    auto data_p = ds.allocate( size );
    std::memcpy( data_p, &test_array[ 0 ], size );

    for ( auto i = std::size_t{}; i < 10ull; ++i )
    {
        REQUIRE( *(static_cast< int* >( data_p ) + i) == static_cast< int >( i ) );
    }
}
