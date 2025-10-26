#include "core/exceptions/runtime_error.hpp"

namespace echo::core::exceptions
{

RuntimeError::RuntimeError(const char *message) : runtime_error(message)
{
}

RuntimeError::RuntimeError(const std::string &message) : runtime_error(message)
{
}

const std::string &RuntimeError::message() const noexcept
{
    return m_message;
}

} // namespace echo::core::exceptions