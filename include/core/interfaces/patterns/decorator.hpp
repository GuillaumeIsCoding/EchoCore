#pragma once
#ifndef ECHO_CORE_DECORATOR_HPP
#define ECHO_CORE_DECORATOR_HPP

#include "core/macros/export.hpp"

#include "core/interfaces/icomponent.hpp"

#include <memory>

namespace echo::core::interfaces::patterns
{

class ECHO_CORE_EXPORT IDecorator
{
  public:
    inline virtual ~IDecorator() = 0;

    inline virtual void execute() = 0;
    inline virtual std::shared_ptr<IComponent> get_wrappee() const = 0;
};

IDecorator::~IDecorator() = default;

} // namespace echo::core::interfaces::patterns

#endif // ECHO_CORE_DECORATOR_HPP