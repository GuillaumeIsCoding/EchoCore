#include "core/buffer.hpp"

#include <cstring>
namespace echo::core
{

Buffer::Buffer() : m_data(nullptr), m_size(0)
{
}

Buffer::Buffer(const Buffer &buffer) : Buffer()
{
    if (buffer.m_data && buffer.m_size > 0)
    {
        allocate(buffer.m_size);
        std::memcpy(m_data, buffer.m_data, buffer.m_size);
    }
}

Buffer::Buffer(uint8 *data, const uint64 &size) : Buffer()
{
    if (data && size > 0)
    {
        allocate(size);
        std::memcpy(m_data, data, size);
    }
}

Buffer::Buffer(const uint64 &size) : m_data(nullptr), m_size(size)
{
    if (size > 0)
    {
        allocate(size);
    }
}

Buffer::Buffer(Buffer &&buffer) noexcept : m_data(buffer.m_data), m_size(buffer.m_size)
{
    buffer.m_data = nullptr;
    buffer.m_size = 0;
}

Buffer &Buffer::operator=(const Buffer &other)
{
    if (this != &other)
    {
        if (other.m_size > 0 && other.m_data)
        {
            uint8 *new_data = new uint8[other.m_size];
            std::memcpy(new_data, other.m_data, other.m_size);

            release();
            m_data = new_data;
            m_size = other.m_size;
        }
        else
        {
            release();
        }
    }

    return *this;
}

Buffer &Buffer::operator=(Buffer &&other) noexcept
{
    if (this != &other)
    {
        release();

        m_data = other.m_data;
        m_size = other.m_size;

        other.m_data = nullptr;
        other.m_size = 0;
    }
    return *this;
}

Buffer::~Buffer()
{
    release();
}

Buffer Buffer::copy(const Buffer &buffer)
{
    Buffer new_buffer;

    if (buffer.m_data && buffer.m_size > 0)
    {
        new_buffer.allocate(buffer.m_size);
        std::memcpy(new_buffer.m_data, buffer.m_data, buffer.m_size);
    }

    return new_buffer;
}

void Buffer::allocate(const uint64 &size)
{
    release();

    m_size = size;

    if (size > 0)
    {
        m_data = new uint8[size];
        m_size = size;

        std::memset(m_data, 0, size);
    }
}

void Buffer::release()
{
    if (m_data)
    {
        delete[] m_data;
        m_data = nullptr;
    }

    m_size = 0;
}

Buffer::operator bool() const
{
    return m_data != nullptr && m_size > 0;
}

uint8 *Buffer::get_data() const
{
    return m_data;
}

uint64 Buffer::get_size() const
{
    return m_size;
}

void Buffer::set_data(uint8 *data)
{
    if (data && m_size)
    {
        allocate(m_size);
        std::memcpy(m_data, data, m_size);
    }
}

void Buffer::set_data(uint8 *data, const uint64 &size)
{

    if (data && size > 0)
    {
        allocate(size);
        std::memcpy(m_data, data, size);
    }
    else
    {
        release();
    }
}

void Buffer::move_from(IBuffer &&other)
{
    if (auto ptr = dynamic_cast<Buffer *>(&other))
    {
        release();

        m_data = ptr->m_data;
        m_size = ptr->m_size;

        ptr->m_data = nullptr;
        ptr->m_size = 0;
    }
}

std::unique_ptr<interfaces::IBuffer> Buffer::clone() const
{
    auto cloned = std::make_unique<Buffer>(m_size);

    if (m_data && m_size > 0)
    {
        cloned->allocate(m_size);
        std::memcpy(cloned->m_data, m_data, m_size);
    }

    return cloned;
}

} // namespace echo::core
