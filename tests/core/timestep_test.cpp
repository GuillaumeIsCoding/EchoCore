#include <catch2/catch_all.hpp>

#include <core/timestep.hpp>

using echo::core::Timestep;

static constexpr float TIME = 100.0f;

TEST_CASE("Timestep", "[timestep][conversion][float]")
{
    Timestep timestep(TIME);

    SECTION("It should return the value passed, when using the float operator")
    {
        REQUIRE((float)timestep == TIME);
    }

    SECTION("It should return the value in seconds, when using get_seconds")
    {
        REQUIRE(timestep.get_seconds() == TIME);
    }

    SECTION("It should return the value in milliseconds, when using get_milliseconds")
    {
        REQUIRE(timestep.get_milliseconds() == TIME * 1000.0f);
    }
}