#include <catch2/catch_all.hpp>

#include <core/timer.hpp>

#include <thread>

using echo::core::Timer;

TEST_CASE("Timer", "[timer][time][float][accuracy]")
{
    Timer timer;

    SECTION("It should reset, when using reset")
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        auto elapsed_before_reset = timer.elapsed();

        timer.reset();

        auto elapsed_after_reset = timer.elapsed();

        REQUIRE(elapsed_after_reset < elapsed_before_reset);
        REQUIRE(elapsed_after_reset == Catch::Approx(0.0f).margin(0.01f));
    }

    SECTION("It should has an accuracy of ±20ms, when using elapsed_milliseconds")
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        auto elapsed_ms = timer.elapsed_milliseconds();

        REQUIRE(elapsed_ms == Catch::Approx(100.0f).margin(20.0f));
    }

    SECTION("It should not be affected by multiple reads")
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        auto first_read = timer.elapsed();
        auto second_read = timer.elapsed();
        auto third_read = timer.elapsed();

        REQUIRE(first_read == Catch::Approx(second_read).margin(0.001f));
        REQUIRE(second_read == Catch::Approx(third_read).margin(0.001f));
    }
}