#include <sstream>
#include <string>

#include <catch2/catch_test_macros.hpp>

#include "nlohmann/json.hpp"

#include "core/settings/json/settings_provider.hpp"

struct SettingsProviderWrapper : public vortex::core::settings::json::SettingsProvider
{
    using vortex::core::settings::json::SettingsProvider::SettingsProvider;

    [[nodiscard]] nlohmann::json * get(std::string const& key)
    {
        return get_object_pointer(key);
    }
};

TEST_CASE("JSON Settings Provider - simple load and get test", "[sample]")
{
    auto sp = SettingsProviderWrapper{};
    auto iss = std::istringstream{ "{\"x\":\"y\"}" };

    sp.load( "x", iss );
    auto const& obj = *sp.get( "x" );

    REQUIRE( obj[ "x" ] == "y" );
}

TEST_CASE("JSON Settings Provider - simple add_and_save and get test", "[sample]")
{
    auto sp = SettingsProviderWrapper{};
    auto oss = std::ostringstream{};
    nlohmann::json obj = { { "x", "y" } };

    sp.add_and_save( "x", &obj, oss );
    auto const& got_obj = *sp.get( "x" );

    REQUIRE( got_obj == obj );
    REQUIRE( oss.str() == "{\n  \"x\": \"y\"\n}\n" );
}
