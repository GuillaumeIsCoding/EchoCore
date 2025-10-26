#include <catch2/catch_all.hpp>

#include <core/logging/client_logger.hpp>

#include <filesystem>

#include <fstream>

namespace fs = std::filesystem;

using echo::core::logging::ClientLogger;

static const std::string FILE_NAME = "dump.log";

static void cleanup()
{
    try
    {
        if (fs::exists(FILE_NAME))
        {
            fs::remove(FILE_NAME);
        }
    }
    catch (...)
    {
        // does not raise any error
    }
}

TEST_CASE("ClientLogger", "[clientlogger][client][logging][spdlog][fmt]")
{
    ClientLogger logger;

    SECTION("It should create the information pointer, when using constructor")
    {
        REQUIRE(logger.get_logger());
        REQUIRE(fs::exists(FILE_NAME));
    }

    cleanup();
}