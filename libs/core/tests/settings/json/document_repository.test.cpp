#include <catch2/catch_test_macros.hpp>
#include "core/settings/json/document_repository.hpp"

TEST_CASE("JSON Document Repository - sample unit test", "[sample]")
{
    vortex::core::settings::json::DocumentRepository();

    REQUIRE(true);
}
