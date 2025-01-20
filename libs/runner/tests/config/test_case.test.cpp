// 
// Unit test source file auto-generated by VORTEX SETTINGS WIZARD
// 
// TODO: Just testing
// 

#include <catch2/catch_test_macros.hpp>
#include <nlohmann/json.hpp>

#include "runner/config/test_case.hpp"

TEST_CASE("TestCase - Sample Test", "[sample]")
{
    vortex::runner::config::TestCase( nullptr );

    REQUIRE(true);
}

// "name" property

TEST_CASE("TestCase - property: \"name\" - getter", "[settings]")
{
    auto obj = nlohmann::json{ { "name", "stest" } };
    auto obj_p = &obj;
    auto s = vortex::runner::config::TestCase{ obj_p };

    auto value = s.name();

    REQUIRE(value == "stest");
}

// "template_name" property

TEST_CASE("TestCase - property: \"template_name\" - getter", "[settings]")
{
    auto obj = nlohmann::json{ { "template_name", "stest" } };
    auto obj_p = &obj;
    auto s = vortex::runner::config::TestCase{ obj_p };

    auto value = s.template_name();

    REQUIRE(value == "stest");
}

// "settings" property

TEST_CASE("TestCase - property: \"settings\" - getter", "[settings]")
{
    nlohmann::json * obj_p = nullptr;
    auto s = vortex::runner::config::TestCase{ obj_p };

    auto value = s.settings();

    REQUIRE(value == nullptr);
}

// "parallel_strategy" property

TEST_CASE("TestCase - property: \"parallel_strategy\" - getter", "[settings]")
{
    nlohmann::json * obj_p = nullptr;
    auto s = vortex::runner::config::TestCase{ obj_p };

    auto value = s.parallel_strategy();

    REQUIRE(value == 0);
}

// "stages" property

TEST_CASE("TestCase - property: \"stages\" - getter", "[settings]")
{
    auto obj = nlohmann::json{ { "stages", "stest" } };
    auto obj_p = &obj;
    auto s = vortex::runner::config::TestCase{ obj_p };

    auto value = s.stages();

    REQUIRE(value == "stest");
}

// "process_count" property

TEST_CASE("TestCase - property: \"process_count\" - getter", "[settings]")
{
    auto obj = nlohmann::json{ { "process_count", -2l } };
    auto obj_p = &obj;
    auto s = vortex::runner::config::TestCase{ obj_p };

    auto value = s.process_count();

    REQUIRE(static_cast< vortex::i32 >( value ) == -2l);
}


