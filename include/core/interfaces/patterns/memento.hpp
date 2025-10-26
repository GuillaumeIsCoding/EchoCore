#pragma once
#ifndef ECHO_CORE_MEMENTO_HPP
#define ECHO_CORE_MEMENTO_HPP

#include "core/macros/export.hpp"

#include <memory>

namespace echo::core::interfaces::patterns
{

class ECHO_CORE_EXPORT IMemento
{
  public:
    inline virtual ~IMemento() = 0;

    inline virtual void restore() = 0;
};

class ECHO_CORE_EXPORT IOriginator
{
  public:
    inline virtual ~IOriginator() = 0;

    inline virtual std::shared_ptr<IMemento> save() = 0;
};

class ECHO_CORE_EXPORT ICareTaker
{
  public:
    inline virtual ~ICareTaker() = 0;

    inline virtual void undo() = 0;
};

IMemento::~IMemento() = default;

IOriginator::~IOriginator() = default;

ICareTaker::~ICareTaker() = default;

} // namespace echo::core::interfaces::patterns

#endif // ECHO_CORE_MEMENTO_HPP