#include <catch2/catch_all.hpp>

#include <core/flags.hpp>

#include <core/macros/utils.hpp>

using echo::core::Flags;

static constexpr uint64 FLAG_1 = ECHO_BIT(0);
static constexpr uint64 FLAG_2 = ECHO_BIT(1);
static constexpr uint64 FLAG_3 = ECHO_BIT(2);

TEST_CASE("Flags", "[flags][bit]")
{
    Flags flags;

    SECTION("It should set multiple flags at the same time, when using set")
    {
        flags.set(FLAG_1 | FLAG_2);

        REQUIRE((flags.has(FLAG_1) && flags.has(FLAG_2)));
    }

    SECTION("It should clear a flag, when using clear")
    {
        flags.set(FLAG_1 | FLAG_3);

        flags.clear(FLAG_1);

        REQUIRE(flags.has(FLAG_3));
        REQUIRE_FALSE(flags.has(FLAG_1));
    }

    SECTION("It should toggle a flag, when using toggle")
    {
        flags.set(FLAG_2 | FLAG_3);

        flags.toggle(FLAG_3);

        REQUIRE(flags.has(FLAG_2));
        REQUIRE_FALSE(flags.has(FLAG_3));
    }

    SECTION("It should reset flags, when using reset")
    {
        flags.set(FLAG_1 | FLAG_2 | FLAG_3);

        flags.reset();

        REQUIRE_FALSE((flags.has(FLAG_1) || flags.has(FLAG_2) || flags.has(FLAG_3)));
    }
}