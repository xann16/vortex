#include <sstream>
#include <utility>

#include <catch2/catch_test_macros.hpp>
#include <nlohmann/json.hpp>

#include "core/settings/json/document_repository.hpp"

TEST_CASE("JSON Document Repository - simple load and save", "[sample]")
{
    auto repo = vortex::core::settings::json::DocumentRepository{};

    auto iss = std::istringstream{ "{\"x\":\"y\"}" };
    auto oss = std::ostringstream{};

    repo.load( "x", iss );
    repo.save( "x", oss );

    REQUIRE( oss.str() == "{\n  \"x\": \"y\"\n}\n" );
}

TEST_CASE("JSON Document Repository - sample add and save", "[sample]")
{
    auto repo = vortex::core::settings::json::DocumentRepository{};

    nlohmann::json obj = { { "x", "y" } };
    auto oss = std::ostringstream{};

    repo.add( "x", &obj );
    repo.save( "x", oss );

    REQUIRE( oss.str() == "{\n  \"x\": \"y\"\n}\n" );
}
