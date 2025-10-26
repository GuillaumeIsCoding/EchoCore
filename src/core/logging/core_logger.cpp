#include "core/logging/core_logger.hpp"

namespace echo::core::logging
{

CoreLogger::CoreLogger() : AbsLogger(DEFAULT_CORE_NAME, DEFAULT_SINK, DEFAULT_FILE_TYPE)
{
}

} // namespace echo::core::logging
