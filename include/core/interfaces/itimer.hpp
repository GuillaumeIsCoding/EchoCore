#pragma once
#ifndef ECHO_CORE_ITIMER_HPP
#define ECHO_CORE_ITIMER_HPP

#include "core/macros/export.hpp"

#include "types.hpp"

namespace echo::core::interfaces
{

class ECHO_CORE_EXPORT ITimer
{
  public:
    inline virtual ~ITimer() = 0;

    inline virtual void reset() = 0;

    inline virtual float elapsed() = 0;
    inline virtual float elapsed_milliseconds() = 0;
};

ITimer::~ITimer() = default;

} // namespace echo::core::interfaces

#endif // ECHO_CORE_ITIMER_HPP