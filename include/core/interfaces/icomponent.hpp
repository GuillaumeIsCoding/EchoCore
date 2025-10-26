#pragma once
#ifndef ECHO_CORE_ICOMPONENT_HPP
#define ECHO_CORE_ICOMPONENT_HPP

#include "core/macros/export.hpp"

namespace echo::core::interfaces
{

class ECHO_CORE_EXPORT IComponent
{
  public:
    inline virtual ~IComponent() = 0;

    inline virtual void execute() = 0;
};

IComponent::~IComponent() = default;

} // namespace echo::core::interfaces

#endif // ECHO_CORE_ICOMPONENT_HPP