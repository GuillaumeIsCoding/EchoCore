#include "core/flags.hpp"

namespace echo::core
{

Flags::Flags() : Flags(DEFAULT_VALUE)
{
}

Flags::Flags(const uint64 &flag) : m_flags(flag)
{
}

void Flags::set(const uint64 &flag)
{
    m_flags |= flag;
}

void Flags::clear(const uint64 &flag)
{
    m_flags &= ~flag;
}

void Flags::toggle(const uint64 &flag)
{
    m_flags ^= flag;
}

void Flags::reset(const uint64 &value)
{
    m_flags = value;
}

bool Flags::has(const uint64 &flag) const
{
    return (m_flags & flag) != 0;
}

} // namespace echo::core
