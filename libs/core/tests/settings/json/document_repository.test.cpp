#include <sstream>

#include <catch2/catch_test_macros.hpp>

#include "core/settings/json/document_repository.hpp"

TEST_CASE("JSON Document Repository - sample unit test", "[sample]")
{
    auto repo = vortex::core::settings::json::DocumentRepository();

    auto iss = std::istringstream{"{\"x\":\"y\"}"};
    auto oss = std::ostringstream{};

    repo.load("x", iss);
    repo.save("x", oss);

    REQUIRE(oss.str() == "{\n  \"x\": \"y\"\n}\n");
}
