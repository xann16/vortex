#include <sstream>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
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
    nlohmann::json obj = { { "x", "y" }, {"null",  nullptr} };
    auto s = vortex::core::settings::json::AnySettings{ &obj };
    auto ossfy = std::ostringstream{};
    auto oss = std::ostringstream{};

    s.stringify(ossfy, 2, 0, false);
    oss << s;

    auto ossfy_result = ossfy.str();
    auto oss_result = oss.str();
    auto str_result = s.to_string();

    const auto expected = "x: y\n";

    REQUIRE(ossfy_result == expected);
    REQUIRE(oss_result == expected);
    REQUIRE(str_result == expected);
}

TEST_CASE("JSON Any Settings - conversion to string - display all", "[settings]")
{
    nlohmann::json obj = { { "x", "y" }, {"null", nullptr} };
    auto s = vortex::core::settings::json::AnySettings{ &obj };
    auto ossfy = std::ostringstream{};
    auto oss = std::ostringstream{};

    s.stringify(ossfy, 2, 0, true);
    oss << std::boolalpha << s;

    auto ossfy_result = ossfy.str();
    auto oss_result = oss.str();

    const auto expected_line_x = "x: y\n";
    const auto expected_line_null = "null: null\n";

    REQUIRE_THAT(ossfy_result, Catch::Matchers::ContainsSubstring( expected_line_x ) );
    REQUIRE_THAT(ossfy_result, Catch::Matchers::ContainsSubstring( expected_line_null ) );
    REQUIRE_THAT(oss_result, Catch::Matchers::ContainsSubstring( expected_line_x ) );
    REQUIRE_THAT(oss_result, Catch::Matchers::ContainsSubstring( expected_line_null ) );
}

TEST_CASE("JSON Any Settings - conversion to string - extra indent size", "[settings]")
{
    nlohmann::json obj = { { "x", { { "y", "z" } } } };
    auto s = vortex::core::settings::json::AnySettings{ &obj };
    auto ossfy = std::ostringstream{};

    s.stringify(ossfy, 4, 0, false);

    auto ossfy_result = ossfy.str();

    const auto expected = "x:\n    y: z\n";

    REQUIRE(ossfy_result == expected);
}

TEST_CASE("JSON Any Settings - conversion to string - extra indent level", "[settings]")
{
    nlohmann::json obj = { { "x", { { "y", "z" } } } };
    auto s = vortex::core::settings::json::AnySettings{ &obj };
    auto ossfy = std::ostringstream{};

    s.stringify(ossfy, 2, 2, false);

    auto ossfy_result = ossfy.str();

    const auto expected = "    x:\n      y: z\n";

    REQUIRE(ossfy_result == expected);
}

TEST_CASE("JSON Any Settings - conversion to string - simple array example", "[settings]")
{
    nlohmann::json obj = { { "x", { "y", "z" } } };
    auto s = vortex::core::settings::json::AnySettings{ &obj };
    auto ossfy = std::ostringstream{};

    s.stringify(ossfy, 2, 0, false);

    auto ossfy_result = ossfy.str();

    const auto expected = "x:\n  - y\n  - z\n";

    REQUIRE(ossfy_result == expected);
}

TEST_CASE("JSON Any Settings - conversion to string - empty array example", "[settings]")
{
    nlohmann::json obj = { { "x", nlohmann::json::array() } };
    auto s = vortex::core::settings::json::AnySettings{ &obj };
    auto ossfy = std::ostringstream{};

    s.stringify(ossfy, 2, 0, false);

    auto ossfy_result = ossfy.str();

    const auto expected = "x: <empty>\n";

    REQUIRE(ossfy_result == expected);
}

TEST_CASE("JSON Any Settings - conversion to string - array of objects example", "[settings]")
{
    nlohmann::json obj = { { "arr", { { { "aa", "x" }, { "ab", "y" } }, { { "ba", "z" }, { "bb", "w" } } } } };
    auto s = vortex::core::settings::json::AnySettings{ &obj };
    auto ossfy = std::ostringstream{};

    s.stringify(ossfy, 2, 0, false);

    auto ossfy_result = ossfy.str();

    const auto expected = "arr:\n  -\n    aa: x\n    ab: y\n  -\n    ba: z\n    bb: w\n";

    REQUIRE(ossfy_result == expected);
}

TEST_CASE("JSON Any Settings - conversion to string for empty", "[settings]")
{
    auto s = vortex::core::settings::json::AnySettings{};
    auto oss = std::ostringstream{};

    oss << s;
    auto oss_result = oss.str();
    auto str_result = s.to_string();

    const auto expected = "<empty>\n";

    REQUIRE(oss_result == expected);
    REQUIRE(str_result == expected);
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

TEST_CASE("JSON Any Settings - equality and inequality operators", "[settings]")
{
    nlohmann::json obj_a = { { "x", "y" } };
    nlohmann::json obj_b = { { "x", "y" } };
    nlohmann::json obj_c = { { "x", "y" }, { "y", "x" }, };

    auto a = vortex::core::settings::json::AnySettings{ &obj_a };
    auto a_bis = vortex::core::settings::json::AnySettings{ &obj_a };
    auto b = vortex::core::settings::json::AnySettings{ &obj_b };
    auto c = vortex::core::settings::json::AnySettings{ &obj_c };

    REQUIRE( a == a );
    REQUIRE( a_bis == a_bis );
    REQUIRE( b == b );
    REQUIRE( c == c );

    REQUIRE( a == a_bis );
    REQUIRE( a == b );
    REQUIRE( a != c );
    REQUIRE( b != c );

    REQUIRE( !( a != a_bis ) );
    REQUIRE( !( a != b ) );
    REQUIRE( !( a == c ) );
    REQUIRE( !( b == c ) );
}

TEST_CASE("JSON Any Settings - equality and inequality operators with empties", "[settings]")
{
    nlohmann::json obj = { { "x", "y" } };

    auto full = vortex::core::settings::json::AnySettings{ &obj };
    auto empty = vortex::core::settings::json::AnySettings{};

    REQUIRE( full != empty );
    REQUIRE( empty != full );
    REQUIRE( empty == empty );

    REQUIRE( !( full == empty ) );
    REQUIRE( !( empty == full ) );
    REQUIRE( !( empty != empty ) );
}
