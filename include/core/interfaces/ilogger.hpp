#pragma once
#ifndef ECHO_CORE_ILOGGER_HPP
#define ECHO_CORE_ILOGGER_HPP

#include "core/macros/export.hpp"

#include "types.hpp"

#include <memory>

namespace spdlog
{

class logger;

namespace sinks
{

class sink;

} // namespace sinks

} // namespace spdlog

namespace echo::core::interfaces
{

class ECHO_CORE_EXPORT ILogger
{
  public:
    inline virtual ~ILogger() = 0;

    inline virtual void init() = 0;

    inline virtual std::shared_ptr<spdlog::logger> get_logger() const = 0;

  protected:
    virtual void init_sink() = 0;
};

ILogger::~ILogger() = default;

} // namespace echo::core::interfaces

#endif // ECHO_CORE_ILOGGER_HPP