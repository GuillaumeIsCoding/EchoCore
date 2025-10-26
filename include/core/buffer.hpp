#pragma once
#ifndef ECHO_CORE_BUFFER_HPP
#define ECHO_CORE_BUFFER_HPP

#include "core/macros/export.hpp"

#include "types.hpp"

#include "core/interfaces/ibuffer.hpp"

namespace echo::core
{

class ECHO_CORE_EXPORT Buffer : public interfaces::IBuffer
{
  public:
    Buffer();
    Buffer(const Buffer &buffer);
    Buffer(uint8 *data, const uint64 &size);
    Buffer(const uint64 &size);
    Buffer(Buffer &&buffer) noexcept;

    Buffer &operator=(const Buffer &other);
    Buffer &operator=(Buffer &&buffer) noexcept;

    ~Buffer() override;

    static Buffer copy(const Buffer &buffer);

    void allocate(const uint64 &size) override;
    void release() override;

    template <typename T> inline T *as();
    template <typename T> inline const T *as_const() const;

    operator bool() const override;

    uint8 *get_data() const override;
    uint64 get_size() const override;

    void set_data(uint8 *data) override;
    void set_data(uint8 *data, const uint64 &size) override;

    void move_from(IBuffer &&other) override;

    std::unique_ptr<IBuffer> clone() const override;

  private:
    uint8 *m_data;
    uint64 m_size;
};

} // namespace echo::core

template <typename T> T *echo::core::Buffer::as()
{
    return reinterpret_cast<T *>(m_data);
}

template <typename T> const T *echo::core::Buffer::as_const() const
{
    return const_cast<const T *>(reinterpret_cast<T *>(m_data));
}

#endif // ECHO_CORE_BUFFER_HPP