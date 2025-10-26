#include "core/exceptions/logic_error.hpp"

namespace echo::core::exceptions
{

LogicError::LogicError(const char *message) : logic_error(message)
{
}

LogicError::LogicError(const std::string &message) : logic_error(message)
{
}

const std::string &LogicError::message() const noexcept
{
    return m_message;
}

} // namespace echo::core::exceptions
