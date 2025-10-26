#include "core/logging/abs_logger.hpp"

#pragma warning(push, 0)

#include <fmt/core.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

#include <spdlog/sinks/basic_file_sink.h>

#pragma warning(pop)

namespace echo::core::logging
{

std::unordered_map<std::string, spdlog::sink_ptr> AbsLogger::s_log_sinks = {};
std::mutex AbsLogger::s_log_sinks_mutex = {};

AbsLogger::AbsLoggerInformation::AbsLoggerInformation(const std::string &_name, const std::string &_sink,
                                                      const FileType &_type, bool _willAppend)
    : name(_name), sink(_sink), type(_type), willAppend(_willAppend)
{
}

AbsLogger::AbsLogger(const std::string &name, const std::string &sink, const FileType &type, bool willAppend)
    : AbsLogger(std::make_shared<AbsLoggerInformation>(name, sink, type, willAppend))
{
}

AbsLogger::AbsLogger(const std::shared_ptr<AbsLoggerInformation> &information)
    : m_information(information), m_logger(nullptr)
{
    init();
}

void AbsLogger::init()
{
    if (!m_logger && !spdlog::get(m_information->name))
    {
        init_sink();

        {
            auto lock = std::lock_guard<std::mutex>(s_log_sinks_mutex);

            auto sink = s_log_sinks.at(m_information->sink);

            m_logger = std::make_shared<spdlog::logger>(m_information->name, sink);
        }

        spdlog::register_logger(m_logger);
        m_logger->set_level(spdlog::level::trace);
        m_logger->flush_on(spdlog::level::trace);
    }
    else
    {
        m_logger = spdlog::get(m_information->name);
    }
}

std::shared_ptr<spdlog::logger> AbsLogger::get_logger() const
{
    return m_logger;
}

void AbsLogger::init_sink()
{
    auto lock = std::lock_guard<std::mutex>(s_log_sinks_mutex);

    if (auto it = s_log_sinks.find(m_information->sink); it == s_log_sinks.end())
    {
        auto file = m_information->sink + "." + to_extension(m_information->type);

        auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(file, !m_information->willAppend);

        sink->set_pattern("[%T] [%l] %n: %v");

        s_log_sinks[m_information->sink] = sink;
    }
}

std::string AbsLogger::to_extension(const FileType &type)
{
    switch (type)
    {
    case Kfile_type_log:
        return "log";
    case Kfile_type_txt:
        return "txt";
    }
    return "";
}

} // namespace echo::core::logging
