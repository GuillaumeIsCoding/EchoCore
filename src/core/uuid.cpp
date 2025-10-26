#include "core/uuid.hpp"

#include <random>

#include <unordered_map>

namespace echo::core
{

static std::random_device s_random_device;
static std::mt19937_64 s_engine(s_random_device());
static std::uniform_int_distribution<uint64> s_uniform_distribution;

Uuid::Uuid() : m_uuid(s_uniform_distribution(s_engine))
{
}

Uuid::Uuid(const uint64 &uuid) : m_uuid(uuid)
{
}

Uuid::operator uint64() const
{
    return m_uuid;
}

} // namespace echo::core
