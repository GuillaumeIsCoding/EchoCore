#include "core/scoped_buffer.hpp"

namespace echo::core
{

ScopedBuffer::ScopedBuffer(Buffer buffer) : m_buffer(buffer)
{
}

ScopedBuffer::ScopedBuffer(const uint64 &size) : m_buffer(size)
{
}

ScopedBuffer::~ScopedBuffer()
{
    m_buffer.release();
}

uint8 *ScopedBuffer::get_data() const
{
    return m_buffer.get_data();
}

uint64 ScopedBuffer::get_size() const
{
    return m_buffer.get_size();
}

ScopedBuffer::operator bool() const
{
    return m_buffer;
}

} // namespace echo::core
