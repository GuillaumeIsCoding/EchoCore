#pragma once
#ifndef ECHO_CORE_RUNTIME_ERROR_HPP
#define ECHO_CORE_RUNTIME_ERROR_HPP

#include "core/macros/export.hpp"

#include "core/interfaces/iexception.hpp"

#include <stdexcept>

namespace echo::core::exceptions
{

class ECHO_CORE_EXPORT RuntimeError : public std::runtime_error, public interfaces::IException
{
  public:
    explicit RuntimeError(const char *message);

    explicit RuntimeError(const std::string &message);

    const std::string &message() const noexcept override;

  protected:
    std::string m_message = what();
};

} // namespace echo::core::exceptions

#endif // ECHO_CORE_RUNTIME_ERROR_HPP