#include "core/timestep.hpp"

namespace echo::core
{

Timestep::Timestep(const float &time) : m_time(time)
{
}

Timestep::operator float() const
{
    return m_time;
}

float Timestep::get_seconds() const
{
    return m_time;
}

float Timestep::get_milliseconds() const
{
    return m_time * 1000.0f;
}

} // namespace echo::core
