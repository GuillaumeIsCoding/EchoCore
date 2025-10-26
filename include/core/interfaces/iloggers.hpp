#pragma once
#ifndef ECHO_CORE_ILOGGERS_HPP
#define ECHO_CORE_ILOGGERS_HPP

#include "core/macros/export.hpp"

#include "types.hpp"

#include "core/interfaces/ilogger.hpp"

#include <memory>

#include <string>

namespace echo::core::interfaces
{

class ECHO_CORE_EXPORT ILoggers
{
  public:
    inline virtual ~ILoggers() = 0;

    inline virtual void add(const std::shared_ptr<ILogger> &logger, const std::string &name) = 0;
    inline virtual void remove(const std::string &name) = 0;

    inline virtual void enable_one(const std::string &name) = 0;
    inline virtual void disable_one(const std::string &name) = 0;

    inline virtual void enable_all() = 0;
    inline virtual void disable_all() = 0;

    inline virtual bool is_enable(const std::string &name) const = 0;

    inline virtual std::shared_ptr<ILogger> find(const std::string &name) const = 0;
};

ILoggers::~ILoggers() = default;

} // namespace echo::core::interfaces

#endif // ECHO_CORE_ILOGGERS_HPP