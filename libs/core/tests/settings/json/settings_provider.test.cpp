#include <catch2/catch_test_macros.hpp>
#include "core/settings/json/settings_provider.hpp"

TEST_CASE("JSON Settings Provider - sample unit test", "[sample]")
{
    vortex::core::settings::json::SettingsProvider();

    REQUIRE(true);
}
