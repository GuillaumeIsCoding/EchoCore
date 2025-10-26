#pragma once
#ifndef ECHO_CORE_TIMER_HPP
#define ECHO_CORE_TIMER_HPP

#include "core/macros/export.hpp"

#include "types.hpp"

#include "core/interfaces/itimer.hpp"

#include <chrono>

namespace echo::core
{

class ECHO_CORE_EXPORT Timer : public interfaces::ITimer
{
  public:
    Timer();

    inline ~Timer() override = default;

    void reset() override;

    float elapsed() override;

    float elapsed_milliseconds() override;

  private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
};

} // namespace echo::core

#endif // ECHO_CORE_TIMER_HPP