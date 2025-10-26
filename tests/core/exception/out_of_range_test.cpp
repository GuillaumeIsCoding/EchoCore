#include <catch2/catch_all.hpp>

#include <core/exceptions/out_of_range_error.hpp>

using echo::core::exceptions::OutOfRangeError;

static void emulate()
{
    throw OutOfRangeError("this is a throw");
}

TEST_CASE("OutOfRangeError", "[outofrangeerror][error]")
{
    SECTION("It should throw RuntimeError with the right message")
    {
        REQUIRE_THROWS_MATCHES(emulate(), OutOfRangeError, Catch::Matchers::Message("this is a throw"));
    }
}