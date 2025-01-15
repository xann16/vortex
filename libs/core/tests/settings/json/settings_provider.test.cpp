#include <sstream>

#include <catch2/catch_test_macros.hpp>
#include "core/settings/json/settings_provider.hpp"
#include "nlohmann/json.hpp"

TEST_CASE("JSON Settings Provider - sample unit test", "[sample]")
{
    auto sp = vortex::core::settings::json::SettingsProvider{};

    auto iss = std::istringstream{ "{\"x\":\"y\"}" };

    sp.load("x", iss);

    auto const& obj = *sp.get("x");

    REQUIRE(obj["x"] == "y");
}
