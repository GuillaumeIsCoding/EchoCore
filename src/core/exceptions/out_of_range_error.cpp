#include "core/exceptions/out_of_range_error.hpp"

namespace echo::core::exceptions
{

OutOfRangeError::OutOfRangeError(const char *message) : out_of_range(message)
{
}

OutOfRangeError::OutOfRangeError(const std::string &message) : out_of_range(message)
{
}

const std::string &OutOfRangeError::message() const noexcept
{
    return m_message;
}

} // namespace echo::core::exceptions