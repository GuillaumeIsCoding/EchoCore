#include <catch2/catch_all.hpp>

#include <core/logging/abs_logger.hpp>

#include <filesystem>

#include <fstream>

namespace fs = std::filesystem;

using echo::core::logging::AbsLogger;

static const std::string LOGGER_NAME = "LOGGER_NAME";
static const std::string SINK_NAME = "sink";
static constexpr int32 FILE_TYPE = echo::core::logging::AbsLogger::FileType::Kfile_type_log;
static constexpr bool WILL_APPEND = true;

static const std::string FILE_NAME = "sink.log";

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

static std::string readLogFile(const std::string &filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        return "";
    }

    std::stringstream buffer;

    buffer << file.rdbuf();
    return buffer.str();
}

TEST_CASE("AbsLoggerInformation", "[absloggerinformation][logging][information][internal]")
{
    SECTION("It should store the information of the logger, when using constructor")
    {
        AbsLogger::AbsLoggerInformation information =
            AbsLogger::AbsLoggerInformation(LOGGER_NAME, SINK_NAME, AbsLogger::FileType::Kfile_type_log, WILL_APPEND);

        REQUIRE(information.name == LOGGER_NAME);
        REQUIRE(information.sink == SINK_NAME);
        REQUIRE(information.type == AbsLogger::FileType::Kfile_type_log);
        REQUIRE(information.willAppend);
    }
}

TEST_CASE("AbsLogger", "[abslogger][logging][spdlog][fmt]")
{
    AbsLogger logger(LOGGER_NAME, SINK_NAME, AbsLogger::FileType::Kfile_type_log, WILL_APPEND);

    SECTION("It should create the information pointer, when using constructor")
    {
        REQUIRE(logger.get_logger());
        REQUIRE(fs::exists(FILE_NAME));
    }

    SECTION("It should return the good value, when using to_extension")
    {
        SECTION("It should return 'log'")
        {
            REQUIRE(AbsLogger::to_extension(AbsLogger::FileType::Kfile_type_log) == "log");
        }

        SECTION("It should return 'txt'")
        {
            REQUIRE(AbsLogger::to_extension(AbsLogger::FileType::Kfile_type_txt) == "txt");
        }
    }

    cleanup();
}