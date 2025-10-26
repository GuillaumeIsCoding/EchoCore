#include "core/logging/client_logger.hpp"

namespace echo::core::logging
{

ClientLogger::ClientLogger() : AbsLogger(DEFAULT_CLIENT_NAME, DEFAULT_SINK, DEFAULT_FILE_TYPE)
{
}

} // namespace echo::core::logging
