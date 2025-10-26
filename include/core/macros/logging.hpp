#pragma once
#ifndef ECHO_CORE_LOGGING_HPP
#define ECHO_CORE_LOGGING_HPP

#include "core/logging/loggers.hpp"

#define ECHO_TRACE(name, ...)                                                                                          \
    ::echo::core::logging::Loggers::get_instance()->log(name, ::echo::core::logging::Loggers::Klog_level_trace,        \
                                                        __VA_ARGS__)
#define ECHO_INFO(name, ...)                                                                                           \
    ::echo::core::logging::Loggers::get_instance()->log(name, ::echo::core::logging::Loggers::Klog_level_info,         \
                                                        __VA_ARGS__)
#define ECHO_DEBUG(name, ...)                                                                                          \
    ::echo::core::logging::Loggers::get_instance()->log(name, ::echo::core::logging::Loggers::Klog_level_debug,        \
                                                        __VA_ARGS__)
#define ECHO_WARN(name, ...)                                                                                           \
    ::echo::core::logging::Loggers::get_instance()->log(name, ::echo::core::logging::Loggers::Klog_level_warn,         \
                                                        __VA_ARGS__)
#define ECHO_ERROR(name, ...)                                                                                          \
    ::echo::core::logging::Loggers::get_instance()->log(name, ::echo::core::logging::Loggers::Klog_level_error,        \
                                                        __VA_ARGS__)
#define ECHO_CRITICAL(name, ...)                                                                                       \
    ::echo::core::logging::Loggers::get_instance()->log(name, ::echo::core::logging::Loggers::Klog_level_critical,     \
                                                        __VA_ARGS__)

#define ECHO_TRACE_M(names, ...)                                                                                       \
    ::echo::core::logging::Loggers::get_instance()->log(names, ::echo::core::logging::Loggers::Klog_level_trace,       \
                                                        __VA_ARGS__)
#define ECHO_INFO_M(names, ...)                                                                                        \
    ::echo::core::logging::Loggers::get_instance()->log(names, ::echo::core::logging::Loggers::Klog_level_info,        \
                                                        __VA_ARGS__)
#define ECHO_DEBUG_M(names, ...)                                                                                       \
    ::echo::core::logging::Loggers::get_instance()->log(names, ::echo::core::logging::Loggers::Klog_level_debug,       \
                                                        __VA_ARGS__)
#define ECHOL_WARN_M(names, ...)                                                                                       \
    ::echo::core::logging::Loggers::get_instance()->log(names, ::echo::core::logging::Loggers::Klog_level_warn,        \
                                                        __VA_ARGS__)
#define ECHO_ERROR_M(names, ...)                                                                                       \
    ::echo::core::logging::Loggers::get_instance()->log(names, ::echo::core::logging::Loggers::Klog_level_error,       \
                                                        __VA_ARGS__)
#define ECHO_CRITICAL_M(names, ...)                                                                                    \
    ::echo::core::logging::Loggers::get_instance()->log(names, ::echo::core::logging::Loggers::Klog_level_critical,    \
                                                        __VA_ARGS__)

#define ECHO_CORE_TRACE(...) ECHO_TRACE(::echo::core::logging::AbsLogger::CORE_NAME, __VA_ARGS__)
#define ECHO_CORE_INFO(...) ECHO_INFO(::echo::core::logging::AbsLogger::CORE_NAME, __VA_ARGS__)
#define ECHO_CORE_DEBUG(...) ECHO_DEBUG(::echo::core::logging::AbsLogger::CORE_NAME, __VA_ARGS__)
#define ECHO_CORE_WARN(...) ECHO_WARN(::echo::core::logging::AbsLogger::CORE_NAME, __VA_ARGS__)
#define ECHO_CORE_ERROR(...) ECHO_ERROR(::echo::core::logging::AbsLogger::CORE_NAME, __VA_ARGS__)
#define ECHO_CORE_CRITICAL(...) ECHO_CRITICAL(::echo::core::logging::AbsLogger::CORE_NAME, __VA_ARGS__)

#define ECHO_CLIENT_TRACE(...) ECHO_TRACE(::echo::core::logging::AbsLogger::CLIENT_NAME, __VA_ARGS__)
#define ECHO_CLIENT_INFO(...) ECHO_INFO(::echo::core::logging::AbsLogger::CLIENT_NAME, __VA_ARGS__)
#define ECHO_CLIENT_DEBUG(...) ECHO_DEBUG(::echo::core::logging::AbsLogger::CLIENT_NAME, __VA_ARGS__)
#define ECHO_CLIENT_WARN(...) ECHO_WARN(::echo::core::logging::AbsLogger::CLIENT_NAME, __VA_ARGS__)
#define ECHO_CLIENT_ERROR(...) ECHO_ERROR(::echo::core::logging::AbsLogger::CLIENT_NAME, __VA_ARGS__)
#define ECHO_CLIENT_CRITICAL(...) ECHO_CRITICAL(::echo::core::logging::AbsLogger::CLIENT_NAME, __VA_ARGS__)

#define ECHO_ADD_LOGGER(logger, name) ::echo::core::logging::Loggers::get_instance()->add(logger, name)

#define ECHO_ADD_CLIENT_LOGGER()                                                                                       \
    ECHO_ADD_LOGGER(std::make_shared<::echo::core::logging::ClientLogger>(),                                           \
                    ::echo::core::logging::AbsLogger::CLIENT_NAME)

#define ECHO_ADD_CORE_LOGGER()                                                                                         \
    ECHO_ADD_LOGGER(std::make_shared<::echo::core::logging::CoreLogger>(), ::echo::core::logging::AbsLogger::CORE_NAME)

#define ECHO_REMOVE_LOGGER(name) ::echo::core::logging::Loggers::get_instance()->remove(name)

#define ECHO_REMOVE_CLIENT_LOGGER() ECHO_REMOVE_LOGGER(::echo::core::logging::AbsLogger::CLIENT_NAME)

#define ECHO_REMOVE_CORE_LOGGER() ECHO_REMOVE_LOGGER(::echo::core::logging::AbsLogger::CORE_NAME)

#define ECHO_ENABLE_ONE(name) ::echo::core::logging::Loggers::get_instance()->enableOne(name)

#define ECHO_DISABLE_ONE(name) ::echo::core::logging::Loggers::get_instance()->disableOne(name)

#define ECHO_ENABLE_ALL() ::echo::core::logging::Loggers::get_instance()->enableAll()

#define ECHO_DISABLE_ALL() ::echo::core::logging::Loggers::get_instance()->disableAll()

#define ECHO_CLEANUP() ::echo::core::logging::Loggers::cleanup()

#endif // ECHO_CORE_LOGGING_HPP