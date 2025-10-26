#pragma once
#ifndef ECHO_CORE_UUID_HPP
#define ECHO_CORE_UUID_HPP

#include "core/macros/export.hpp"

#include "types.hpp"

#include "core/interfaces/iuuid.hpp"

namespace echo::core
{

class ECHO_CORE_EXPORT Uuid : public interfaces::IUuid
{
  public:
    Uuid();
    Uuid(const uint64 &uuid);
    Uuid(const Uuid &) = default;

    inline ~Uuid() override = default;

    operator uint64() const override;

  private:
    uint64 m_uuid;
};

} // namespace echo::core

namespace std
{

template <typename T> struct hash;

template <> struct hash<echo::core::Uuid>
{
    inline std::size_t operator()(const echo::core::Uuid &uuid) const
    {
        return (uint64)uuid;
    }
};

} // namespace std

#endif // ECHO_CORE_UUID_HPP