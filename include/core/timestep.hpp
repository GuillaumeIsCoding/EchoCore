#pragma once
#ifndef ECHO_CORE_TIMESTEP_HPP
#define ECHO_CORE_TIMESTEP_HPP

#include "core/macros/export.hpp"

#include "types.hpp"

#include "core/interfaces/itimestep.hpp"

namespace echo::core
{

class ECHO_CORE_EXPORT Timestep : public interfaces::ITimestep
{
  public:
    Timestep(const float &time = 0.0f);

    inline ~Timestep() override = default;

    operator float() const override;

    float get_seconds() const override;
    float get_milliseconds() const override;

  private:
    float m_time;
};

} // namespace echo::core

#endif // ECHO_CORE_TIMESTEP_HPP