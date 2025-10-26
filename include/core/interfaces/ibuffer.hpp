#pragma once
#ifndef ECHO_CORE_IBUFFER_HPP
#define ECHO_CORE_IBUFFER_HPP

#include "core/macros/export.hpp"

#include "types.hpp"

namespace echo::core::interfaces
{

class ECHO_CORE_EXPORT IBuffer
{
  public:
    inline virtual ~IBuffer() = 0;

    inline virtual void allocate(const uint64 &size) = 0;
    inline virtual void release() = 0;

    inline virtual operator bool() const = 0;

    inline virtual uint8 *get_data() const = 0;
    inline virtual uint64 get_size() const = 0;

    inline virtual void set_data(uint8 *data) = 0;
    inline virtual void set_data(uint8 *data, const uint64 &size) = 0;

    inline virtual void move_from(IBuffer &&other) = 0;

    inline virtual std::unique_ptr<IBuffer> clone() const = 0;
};

IBuffer::~IBuffer() = default;

} // namespace echo::core::interfaces

#endif // ECHO_CORE_IBUFFER_HPP