#pragma once
#ifndef ECHO_CORE_OUT_OF_RANGE_ERROR_HPP
#define ECHO_CORE_OUT_OF_RANGE_ERROR_HPP

#include "core/macros/export.hpp"

#include "core/interfaces/iexception.hpp"

#include <stdexcept>

namespace echo::core::exceptions
{

class ECHO_CORE_EXPORT OutOfRangeError : public std::out_of_range, public interfaces::IException
{
  public:
    explicit OutOfRangeError(const char *message);

    explicit OutOfRangeError(const std::string &message);

    const std::string &message() const noexcept override;

  protected:
    std::string m_message = what();
};

} // namespace echo::core::exceptions

#endif // ECHO_CORE_OUT_OF_RANGE_ERROR_HPP