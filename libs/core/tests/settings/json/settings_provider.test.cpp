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

TEST_CASE("JSON Settings Provider - sample unit test", "[sample]")
{
    auto sp = SettingsProviderWrapper{};

    auto iss = std::istringstream{ "{\"x\":\"y\"}" };

    sp.load("x", iss);

    auto const& obj = *sp.get("x");

    REQUIRE(obj["x"] == "y");
}
