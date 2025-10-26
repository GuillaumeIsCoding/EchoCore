#include <catch2/catch_all.hpp>

#include <core/uuid.hpp>

using echo::core::Uuid;

static const uint64 UUID = 1000;

TEST_CASE("Uuid", "[uuid][UUID][unique]")
{
    SECTION("Uuid default constructor")
    {
        auto uuid_1 = Uuid();
        auto uuid_2 = Uuid();

        REQUIRE((uint64)uuid_1 != (uint64)uuid_2);
    }

    SECTION("Uuid copy constructor")
    {
        auto uuid_1 = Uuid();
        auto uuid_2 = Uuid(uuid_1);

        REQUIRE((uint64)uuid_1 == (uint64)uuid_2);
    }

    SECTION("Uuid uint64 constructor")
    {
        auto uuid_1 = Uuid(UUID);

        REQUIRE((uint64)uuid_1 == UUID);
    }
}