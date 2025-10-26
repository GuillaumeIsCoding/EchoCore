#pragma once
#ifndef ECHO_CORE_ITIMESTEP_HPP
#define ECHO_CORE_ITIMESTEP_HPP

#include "core/macros/export.hpp"

#include "types.hpp"

namespace echo::core::interfaces
{

class ECHO_CORE_EXPORT ITimestep
{
  public:
    inline virtual ~ITimestep() = 0;

    inline virtual operator float() const = 0;

    inline virtual float get_seconds() const = 0;
    inline virtual float get_milliseconds() const = 0;
};

ITimestep::~ITimestep() = default;

} // namespace echo::core::interfaces

#endif // ECHO_CORE_ITIMESTEP_HPP