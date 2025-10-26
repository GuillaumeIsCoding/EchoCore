#pragma once
#ifndef ECHO_CORE_PROTOTYPE_HPP
#define ECHO_CORE_PROTOTYPE_HPP

#include "core/macros/export.hpp"

#include <memory>

namespace echo::core::interfaces::patterns
{

class ECHO_CORE_EXPORT IPrototype
{
  public:
    inline virtual ~IPrototype() = 0;

    inline virtual std::shared_ptr<IPrototype> clone() const = 0;
};

IPrototype::~IPrototype() = default;

} // namespace echo::core::interfaces::patterns

#endif // ECHO_CORE_PROTOTYPE_HPP