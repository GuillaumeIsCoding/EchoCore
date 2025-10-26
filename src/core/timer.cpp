#include "core/timer.hpp"

namespace echo::core
{

Timer::Timer()
{
    reset();
}

void Timer::reset()
{
    m_start = std::chrono::high_resolution_clock::now();
}

float Timer::elapsed()
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_start)
               .count() *
           0.001f * 0.001f * 0.001f;
}

float Timer::elapsed_milliseconds()
{
    return elapsed() * 1000.0f;
}

} // namespace echo::core
