#pragma once
#ifndef ECHO_CORE_SCOPED_BUFFER_HPP
#define ECHO_CORE_SCOPED_BUFFER_HPP

#include "core/macros/export.hpp"

#include "types.hpp"

#include "core/buffer.hpp"

#include "core/interfaces/iscoped_buffer.hpp"

namespace echo::core
{

class ECHO_CORE_EXPORT ScopedBuffer : public interfaces::IScopedBuffer
{
  public:
    ScopedBuffer(Buffer buffer);
    ScopedBuffer(const uint64 &size);

    ~ScopedBuffer() override;

    uint8 *get_data() const override;
    uint64 get_size() const override;

    template <typename T> inline T *as();
    template <typename T> inline const T *as_const() const;

    operator bool() const override;

  private:
    Buffer m_buffer;
};

} // namespace echo::core

template <typename T> T *echo::core::ScopedBuffer::as()
{
    return m_buffer.as<T>();
}

template <typename T> const T *echo::core::ScopedBuffer::as_const() const
{
    return m_buffer.as_const<T>();
}

#endif // ECHO_CORE_SCOPED_BUFFER_HPP