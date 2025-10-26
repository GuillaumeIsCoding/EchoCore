#pragma once
#ifndef ECHO_CORE_IFLAGS_HPP
#define ECHO_CORE_IFLAGS_HPP

#include "core/macros/export.hpp"

#include "types.hpp"

namespace echo::core::interfaces
{

class ECHO_CORE_EXPORT IFlags
{
  protected:
    static constexpr uint64 DEFAULT_VALUE = 0;

  public:
    inline virtual ~IFlags() = 0;

    inline virtual void set(const uint64 &flag) = 0;
    inline virtual void clear(const uint64 &flag) = 0;
    inline virtual void toggle(const uint64 &flag) = 0;
    inline virtual void reset(const uint64 &value) = 0;

    inline virtual bool has(const uint64 &flag) const = 0;
};

IFlags::~IFlags() = default;

} // namespace echo::core::interfaces

#endif // ECHO_CORE_IFLAGS_HPP