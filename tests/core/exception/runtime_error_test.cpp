#include <catch2/catch_all.hpp>

#include <core/exceptions/runtime_error.hpp>

using echo::core::exceptions::RuntimeError;

static void emulate()
{
    throw RuntimeError("this is a throw");
}

TEST_CASE("RuntimeError", "[runtimeerror][error]")
{
    SECTION("It should throw RuntimeError with the right message")
    {
        REQUIRE_THROWS_MATCHES(emulate(), RuntimeError, Catch::Matchers::Message("this is a throw"));
    }
}