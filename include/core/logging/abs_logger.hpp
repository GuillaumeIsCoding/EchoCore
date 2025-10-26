#pragma once
#ifndef ECHO_CORE_ABS_LOGGER_HPP
#define ECHO_CORE_ABS_LOGGER_HPP

#include "core/macros/export.hpp"

#include "types.hpp"

#include "core/interfaces/ilogger.hpp"

namespace echo::core::logging
{

class ECHO_CORE_EXPORT AbsLogger : public interfaces::ILogger
{
  public:
    enum FileType
    {
        Kfile_type_log,
        Kfile_type_txt
    };

    struct ECHO_CORE_EXPORT AbsLoggerInformation
    {
        AbsLoggerInformation(const std::string &_name, const std::string &_sink, const FileType &_type,
                             bool _willAppend = false);

        std::string name;
        std::string sink;
        FileType type;
        bool willAppend;
    };

    inline static const std::string DEFAULT_CORE_NAME = "CORE";
    inline static const std::string DEFAULT_CLIENT_NAME = "CLIENT";

    inline static const std::string DEFAULT_SINK = "dump";

    inline static const FileType DEFAULT_FILE_TYPE = FileType::Kfile_type_log;

    AbsLogger(const std::string &name, const std::string &sink, const FileType &type, bool willAppend = false);

    AbsLogger(const std::shared_ptr<AbsLoggerInformation> &information);

    inline virtual ~AbsLogger() override;

    virtual void init() override;

    virtual std::shared_ptr<spdlog::logger> get_logger() const override;

    static std::string to_extension(const FileType &type);

  protected:
    virtual void init_sink() override;

    std::shared_ptr<AbsLoggerInformation> m_information;
    std::shared_ptr<spdlog::logger> m_logger;

    static std::unordered_map<std::string, std::shared_ptr<spdlog::sinks::sink>> s_log_sinks;
    static std::mutex s_log_sinks_mutex;
};

AbsLogger::~AbsLogger() = default;

} // namespace echo::core::logging

#endif // ECHO_CORE_ABS_LOGGER_HPP