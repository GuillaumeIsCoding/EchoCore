#pragma once
#ifndef ECHO_CORE_FLAGS_HPP
#define ECHO_CORE_FLAGS_HPP

#include "core/macros/export.hpp"

#include "types.hpp"

#include "core/interfaces/iflags.hpp"

namespace echo::core
{

class ECHO_CORE_EXPORT Flags : public interfaces::IFlags
{
  public:
    Flags();
    Flags(const uint64 &flag);

    inline ~Flags() override;

    void set(const uint64 &flag) override;
    void clear(const uint64 &flag) override;
    void toggle(const uint64 &flag) override;
    void reset(const uint64 &value = DEFAULT_VALUE) override;

    bool has(const uint64 &flag) const override;

  protected:
    uint64 m_flags;
};

Flags::~Flags() = default;

} // namespace echo::core

#endif // ECHO_CORE_FLAGS_HPP