#include <catch2/catch_all.hpp>

#include <core/exceptions/logic_error.hpp>

using echo::core::exceptions::LogicError;

static void emulate()
{
    throw LogicError("this is a throw");
}

TEST_CASE("LogicError", "[logicerror][error]")
{
    SECTION("It should throw RuntimeError with the right message")
    {
        REQUIRE_THROWS_MATCHES(emulate(), LogicError, Catch::Matchers::Message("this is a throw"));
    }
}