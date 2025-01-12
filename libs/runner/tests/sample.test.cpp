#include <catch2/catch_test_macros.hpp>
#include <runner/sample.hpp>

TEST_CASE("Sample unit test", "[sample]")
{
    REQUIRE(vortex::answer() == 42);
}
