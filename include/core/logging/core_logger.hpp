#pragma once
#ifndef ECHO_CORE_CORE_LOGGER_HPP
#define ECHO_CORE_CORE_LOGGER_HPP

#include "core/macros/export.hpp"

#include "types.hpp"

#include "core/logging/abs_logger.hpp"

namespace echo::core::logging
{

class ECHO_CORE_EXPORT CoreLogger : public AbsLogger
{
  public:
    CoreLogger();
};

} // namespace echo::core::logging

#endif // ECHO_CORE_CORE_LOGGER_HPP