#include <catch2/catch_all.hpp>

#include <core/logging/loggers.hpp>

#include <chrono>

#include <filesystem>

#include <fstream>

#include <thread>

#include <iostream>

namespace fs = std::filesystem;

using echo::core::logging::ClientLogger;
using echo::core::logging::CoreLogger;
using echo::core::logging::Loggers;

static const std::string FILE_NAME = "dump.log";

static void cleanup()
{
    Loggers::cleanup();

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

static std::string readFile(const std::string &filename)
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

TEST_CASE("Loggers", "[loggers][logging][manager][spdlog][fmt][template]")
{
    auto client = std::make_shared<ClientLogger>();
    auto core = std::make_shared<CoreLogger>();
    auto loggers = Loggers::get_instance();

    std::list<std::string> names = {"core", "client"};

    SECTION("It should only return one instance of the class, when using get_instance")
    {
        REQUIRE((loggers == Loggers::get_instance()));
    }

    SECTION("It should add a logger to Loggers, when using add")
    {
        loggers->add(core, "core");

        REQUIRE(loggers->find("core"));
    }

    SECTION("It should handle quietly and not add a logger, if already existing, when using add")
    {
        loggers->add(core, "core");

        loggers->add(client, "core");

        REQUIRE_NOTHROW(loggers->remove("core"));
    }

    SECTION("It should not add a logger, if already exists, when using add")
    {
        loggers->add(core, "core");

        loggers->add(client, "core");

        REQUIRE((core == loggers->find("core")));
    }

    SECTION("It should remove a logger from logger, when using remove")
    {
        loggers->add(client, "client");

        REQUIRE(loggers->find("client"));

        loggers->remove("client");

        REQUIRE_FALSE(loggers->find("client"));
    }

    SECTION("It should handle quietly when not found, when using remove")
    {
        REQUIRE_NOTHROW(loggers->remove("core"));
    }

    SECTION("It should return nullptr, if not found, when using find")
    {
        REQUIRE_FALSE(loggers->find("core"));
    }

    SECTION("It should disable one logger, when using disable_one")
    {
        loggers->add(core, "core");
        loggers->add(client, "client");

        loggers->disable_one("client");

        REQUIRE((loggers->is_enable("core") && !loggers->is_enable("client")));
    }

    SECTION("It should disable all logger, when using disable_all")
    {
        loggers->add(core, "core");
        loggers->add(client, "client");

        loggers->disable_all();

        REQUIRE_FALSE((loggers->is_enable("core") || loggers->is_enable("client")));
    }

    SECTION("It should enable one logger, when using enabel_one")
    {
        loggers->add(core, "core");
        loggers->add(client, "client");

        loggers->disable_all();

        loggers->enable_one("client");

        REQUIRE((!loggers->is_enable("core") && loggers->is_enable("client")));
    }

    SECTION("It should enable all logger, when using enable_all")
    {
        loggers->add(core, "core");
        loggers->add(client, "client");

        loggers->disable_all();

        loggers->enable_all();

        REQUIRE((loggers->is_enable("core") && loggers->is_enable("client")));
    }

    SECTION("It should be able to write trace level message to multiple loggers, with multiple args, when using log")
    {
        loggers->add(core, "core");
        loggers->add(client, "client");

        loggers->log(names, Loggers::Klog_level_trace, "this is a log message with values at the end {} : {}", 10,
                     "string");

        std::string content = readFile(FILE_NAME);

        REQUIRE_THAT(content,
                     Catch::Matchers::ContainsSubstring("this is a log message with values at the end 10 : string"));
    }

    SECTION("It should be able to write info level message to multiple loggers, with multiple args, when using log")
    {
        loggers->add(core, "core");
        loggers->add(client, "client");

        loggers->log(names, Loggers::Klog_level_info, "this is a log message with values at the end {} : {}", 10,
                     "string");

        std::string content = readFile(FILE_NAME);

        REQUIRE_THAT(content,
                     Catch::Matchers::ContainsSubstring("this is a log message with values at the end 10 : string"));
    }

    SECTION("It should be able to write warn level message to multiple loggers, with multiple args, when using log")
    {
        loggers->add(core, "core");
        loggers->add(client, "client");

        loggers->log(names, Loggers::Klog_level_warn, "this is a log message with values at the end {} : {}", 10,
                     "string");

        std::string content = readFile(FILE_NAME);

        REQUIRE_THAT(content,
                     Catch::Matchers::ContainsSubstring("this is a log message with values at the end 10 : string"));
    }

    SECTION("It should be able to write debug level message to multiple loggers, with multiple args, when using log")
    {
        loggers->add(core, "core");
        loggers->add(client, "client");

        loggers->log(names, Loggers::Klog_level_debug, "this is a log message with values at the end {} : {}", 10,
                     "string");

        std::string content = readFile(FILE_NAME);

        REQUIRE_THAT(content,
                     Catch::Matchers::ContainsSubstring("this is a log message with values at the end 10 : string"));
    }

    SECTION("It should be able to write error level message to multiple loggers, with multiple args, when using log")
    {
        loggers->add(core, "core");
        loggers->add(client, "client");

        loggers->log(names, Loggers::Klog_level_error, "this is a log message with values at the end {} : {}", 10,
                     "string");

        std::string content = readFile(FILE_NAME);

        REQUIRE_THAT(content,
                     Catch::Matchers::ContainsSubstring("this is a log message with values at the end 10 : string"));
    }

    SECTION("It should be able to write critical level message to multiple loggers, with multiple args, when using log")
    {
        loggers->add(core, "core");
        loggers->add(client, "client");

        loggers->log(names, Loggers::Klog_level_critical, "this is a log message with values at the end {} : {}", 10,
                     "string");

        std::string content = readFile(FILE_NAME);

        REQUIRE_THAT(content,
                     Catch::Matchers::ContainsSubstring("this is a log message with values at the end 10 : string"));
    }

    SECTION("It should be able to write trace level message to multiple loggers, with 0 args, when using log")
    {
        loggers->add(core, "core");
        loggers->add(client, "client");

        loggers->log(names, Loggers::Klog_level_trace, "this is a log message with values at the end");

        std::string content = readFile(FILE_NAME);

        REQUIRE_THAT(content, Catch::Matchers::ContainsSubstring("this is a log message with values at the end"));
    }

    SECTION("It should be able to write info level message to multiple loggers, with 0 args, when using log")
    {
        loggers->add(core, "core");
        loggers->add(client, "client");

        loggers->log(names, Loggers::Klog_level_info, "this is a log message with values at the end");

        std::string content = readFile(FILE_NAME);

        REQUIRE_THAT(content, Catch::Matchers::ContainsSubstring("this is a log message with values at the end"));
    }

    SECTION("It should be able to write warn level message to multiple loggers, with 0 args, when using log")
    {
        loggers->add(core, "core");
        loggers->add(client, "client");

        loggers->log(names, Loggers::Klog_level_warn, "this is a log message with values at the end");

        std::string content = readFile(FILE_NAME);

        REQUIRE_THAT(content, Catch::Matchers::ContainsSubstring("this is a log message with values at the end"));
    }

    SECTION("It should be able to write debug level message to multiple loggers, with 0 args, when using log")
    {
        loggers->add(core, "core");
        loggers->add(client, "client");

        loggers->log(names, Loggers::Klog_level_debug, "this is a log message with values at the end");

        std::string content = readFile(FILE_NAME);

        REQUIRE_THAT(content, Catch::Matchers::ContainsSubstring("this is a log message with values at the end"));
    }

    SECTION("It should be able to write error level message to multiple loggers, with 0 args, when using log")
    {
        loggers->add(core, "core");
        loggers->add(client, "client");

        loggers->log(names, Loggers::Klog_level_error, "this is a log message with values at the end");

        std::string content = readFile(FILE_NAME);

        REQUIRE_THAT(content, Catch::Matchers::ContainsSubstring("this is a log message with values at the end"));
    }

    SECTION("It should be able to write critical level message to multiple loggers, with 0 args, when using log")
    {
        loggers->add(core, "core");
        loggers->add(client, "client");

        loggers->log(names, Loggers::Klog_level_critical, "this is a log message with values at the end");

        std::string content = readFile(FILE_NAME);

        REQUIRE_THAT(content, Catch::Matchers::ContainsSubstring("this is a log message with values at the end"));
    }

    cleanup();
}
