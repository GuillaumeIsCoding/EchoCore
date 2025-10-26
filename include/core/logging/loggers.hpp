#pragma once
#ifndef ECHO_CORE_LOGGERS_HPP
#define ECHO_CORE_LOGGERS_HPP

#include "core/macros/export.hpp"

#include "types.hpp"

#include "core/interfaces/iloggers.hpp"

#include "core/logging/abs_logger.hpp"

#include "core/logging/client_logger.hpp"

#include "core/logging/core_logger.hpp"

#pragma warning(push, 0)

#include <fmt/core.h>

#include <spdlog/fmt/ostr.h>

#include <spdlog/spdlog.h>

#pragma warning(pop)

namespace echo::core::logging
{

class ECHO_CORE_EXPORT Loggers : public interfaces::ILoggers
{
    static std::unique_ptr<Loggers> s_instance;
    static std::mutex s_loggers_mutex;

    Loggers() = default;

  public:
    enum LogLevel
    {
        Klog_level_trace,
        Klog_level_info,
        Klog_level_warn,
        Klog_level_debug,
        Klog_level_error,
        Klog_level_critical
    };

    inline virtual ~Loggers() override = default;

    static Loggers *get_instance();
    static void cleanup();

    virtual void add(const std::shared_ptr<interfaces::ILogger> &logger, const std::string &name) override;
    virtual void remove(const std::string &name) override;

    template <typename... Args> inline void log(const std::string &name, const LogLevel &level, Args &&...args);

    template <typename... Args>
    inline void log(const std::list<std::string> &names, const LogLevel &level, Args &&...args);

    virtual void enable_one(const std::string &name) override;
    virtual void disable_one(const std::string &name) override;

    virtual void enable_all() override;
    virtual void disable_all() override;

    virtual bool is_enable(const std::string &name) const override;

    virtual std::shared_ptr<interfaces::ILogger> find(const std::string &name) const override;

  private:
    template <typename FormatString, typename... Args>
    inline void log(const std::pair<bool, std::shared_ptr<interfaces::ILogger>> &value, const LogLevel &level,
                    const FormatString &format, Args &&...args);

    template <typename T>
    inline void log(const std::pair<bool, std::shared_ptr<interfaces::ILogger>> &value, const LogLevel &level, T &&msg);

    std::unordered_map<std::string, std::pair<bool, std::shared_ptr<interfaces::ILogger>>> m_loggers;
};

template <typename... Args> void Loggers::log(const std::string &name, const LogLevel &level, Args &&...args)
{
    auto lock = std::lock_guard<std::mutex>(s_loggers_mutex);

    if (auto it = m_loggers.find(name); it != m_loggers.end())
    {
        log(it->second, level, std::forward<Args>(args)...);
    }
}

template <typename... Args>
void Loggers::log(const std::list<std::string> &names, const LogLevel &level, Args &&...args)
{
    auto lock = std::lock_guard<std::mutex>(s_loggers_mutex);

    std::vector<std::pair<bool, std::shared_ptr<interfaces::ILogger>>> loggers;

    for (const auto &name : names)
    {
        if (auto it = m_loggers.find(name); it != m_loggers.end())
        {
            loggers.push_back(it->second);
        }
    }

    for (auto &p : loggers)
    {
        if (p.first)
        {
            log(p, level, std::forward<Args>(args)...);
        }
    }
}

template <typename FormatString, typename... Args>
void Loggers::log(const std::pair<bool, std::shared_ptr<interfaces::ILogger>> &value, const LogLevel &level,
                  const FormatString &format, Args &&...args)
{
    if (auto logger = value.second; value.first && logger)
    {
        switch (level)
        {
        case Klog_level_trace:
            logger->get_logger()->trace(fmt::runtime(format), std::forward<Args>(args)...);
            break;
        case Klog_level_info:
            logger->get_logger()->info(fmt::runtime(format), std::forward<Args>(args)...);
            break;
        case Klog_level_warn:
            logger->get_logger()->warn(fmt::runtime(format), std::forward<Args>(args)...);
            break;
        case Klog_level_debug:
            logger->get_logger()->debug(fmt::runtime(format), std::forward<Args>(args)...);
            break;
        case Klog_level_error:
            logger->get_logger()->error(fmt::runtime(format), std::forward<Args>(args)...);
            break;
        case Klog_level_critical:
            logger->get_logger()->critical(fmt::runtime(format), std::forward<Args>(args)...);
            break;
        }
    }
}

template <typename T>
void Loggers::log(const std::pair<bool, std::shared_ptr<interfaces::ILogger>> &value, const LogLevel &level, T &&msg)
{
    if (auto logger = value.second; value.first && logger)
    {
        switch (level)
        {
        case Klog_level_trace:
            logger->get_logger()->trace("{}", std::forward<T>(msg));
            break;
        case Klog_level_info:
            logger->get_logger()->info("{}", std::forward<T>(msg));
            break;
        case Klog_level_warn:
            logger->get_logger()->warn("{}", std::forward<T>(msg));
            break;
        case Klog_level_debug:
            logger->get_logger()->debug("{}", std::forward<T>(msg));
            break;
        case Klog_level_error:
            logger->get_logger()->error("{}", std::forward<T>(msg));
            break;
        case Klog_level_critical:
            logger->get_logger()->critical("{}", std::forward<T>(msg));
            break;
        }
    }
}

} // namespace echo::core::logging

#endif // ECHO_CORE_LOGGERS_HPP