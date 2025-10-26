#pragma once
#ifndef ECHO_CORE_ISCOPED_BUFFER_HPP
#define ECHO_CORE_ISCOPED_BUFFER_HPP

#include "core/macros/export.hpp"

#include "types.hpp"

namespace echo::core::interfaces
{

class ECHO_CORE_EXPORT IScopedBuffer
{
  public:
    inline virtual ~IScopedBuffer() = 0;

    inline virtual uint8 *get_data() const = 0;
    inline virtual uint64 get_size() const = 0;

    inline virtual operator bool() const = 0;
};

IScopedBuffer::~IScopedBuffer() = default;

} // namespace echo::core::interfaces

#endif // ECHO_CORE_ISCOPED_BUFFER_HPP