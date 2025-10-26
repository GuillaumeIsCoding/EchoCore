#pragma once
#ifndef ECHO_CORE_IEXCEPTION_HPP
#define ECHO_CORE_IEXCEPTION_HPP

#include "core/macros/export.hpp"

#include <string>

namespace echo::core::interfaces
{

class ECHO_CORE_EXPORT IException
{
  public:
    inline virtual ~IException() = 0;

    inline virtual const std::string &message() const noexcept = 0;
};

IException::~IException() = default;

} // namespace echo::core::interfaces

#endif // ECHO_CORE_IEXCEPTION_HPP