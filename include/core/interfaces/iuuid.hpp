#pragma once
#ifndef ECHO_CORE_IUUID_HPP
#define ECHO_CORE_IUUID_HPP

#include "core/macros/export.hpp"

#include "types.hpp"

namespace echo::core::interfaces
{

class ECHO_CORE_EXPORT IUuid
{
  public:
    inline virtual ~IUuid() = 0;

    inline virtual operator uint64() const = 0;
};

IUuid::~IUuid() = default;

} // namespace echo::core::interfaces

#endif // ECHO_CORE_IUUID_HPP