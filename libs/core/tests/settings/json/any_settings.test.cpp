#include <sstream>

#include <catch2/catch_test_macros.hpp>
#include <nlohmann/json.hpp>

#include "core/settings/json/any_settings.hpp"

TEST_CASE("JSON Any Settings - basic test", "[settings]")
{
    nlohmann::json obj = { { "x", "y" } };
    auto s = vortex::core::settings::json::AnySettings{ &obj };

    REQUIRE(!s.is_empty());

    auto data_p = s.data();

    REQUIRE(data_p != nullptr);
    REQUIRE(obj == *data_p);
}

TEST_CASE("JSON Any Settings - basic empty test", "[settings]")
{
    auto s = vortex::core::settings::json::AnySettings{};

    REQUIRE(s.is_empty());
    REQUIRE(s.data() == nullptr);
}

TEST_CASE("JSON Any Settings - conversion to string", "[settings]")
{
    nlohmann::json obj = { { "x", "y" } };
    auto s = vortex::core::settings::json::AnySettings{ &obj };
    auto oss = std::ostringstream{};

    oss << s;
    auto oss_result = oss.str();
    auto str_result = s.to_string();

    const auto expected = "{\n  \"x\": \"y\"\n}\n";

    REQUIRE(oss_result == expected);
    REQUIRE(str_result == expected);
}

TEST_CASE("JSON Any Settings - conversion to string for empty", "[settings]")
{
    auto s = vortex::core::settings::json::AnySettings{};
    auto oss = std::ostringstream{};

    oss << s;
    auto oss_result = oss.str();
    auto str_result = s.to_string();

    REQUIRE(oss_result == "");
    REQUIRE(str_result == "");
}

TEST_CASE("JSON Any Settings - merge", "[settings]")
{
    nlohmann::json obj =
    {
        { "str", "test" },
        { "obj", { { "x", "y" } } },
        { "int", 1 }
    };
    nlohmann::json patch =
    {
        { "str", "release" },
        { "obj", { { "y", "x" } } },
        { "bool", true }
    };
    auto s = vortex::core::settings::json::AnySettings{ &obj };
    auto p = vortex::core::settings::json::AnySettings{ &patch };

    s.merge( p );

    nlohmann::json expected =
    {
        { "str", "release" },
        { "obj", { { "x", "y" }, { "y", "x" } } },
        { "int", 1 },
        { "bool", true }
    };

    REQUIRE(*(s.data()) == expected);
}

TEST_CASE("JSON Any Settings - merge with removal", "[settings]")
{
    nlohmann::json obj =
    {
        { "str", "test" },
        { "obj", { { "x", "y" } } },
        { "obj_to_remove", { { "y", "x" } } },
        { "int", 1 }
    };
    nlohmann::json patch =
    {
        { "str", "release" },
        { "obj", { { "x", nullptr } } },
        { "obj_to_remove", nullptr },
        { "int", nullptr }
    };
    auto s = vortex::core::settings::json::AnySettings{ &obj };

    s.merge( &patch );

    nlohmann::json expected =
    {
        { "str", "release" },
        { "obj", nlohmann::json::object() }
    };

    REQUIRE(*(s.data()) == expected);
}

TEST_CASE("JSON Any Settings - merge with empties", "[settings]")
{
    nlohmann::json obj = { { "x", "y" } };
    auto empty = vortex::core::settings::json::AnySettings{};
    auto full = vortex::core::settings::json::AnySettings{ &obj };

    REQUIRE( empty.is_empty() );
    REQUIRE( !full.is_empty() );

    empty.merge( full );

    REQUIRE( empty.is_empty() );

    full.merge( empty );

    REQUIRE( !full.is_empty() );
    REQUIRE( *(full.data()) == obj );
}
