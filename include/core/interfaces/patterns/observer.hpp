#pragma once
#ifndef ECHO_CORE_OBSERVER_HPP
#define ECHO_CORE_OBSERVER_HPP

#include "core/macros/export.hpp"

#include <memory>

namespace echo::core::interfaces::patterns
{

template <typename T> class IObserver
{
  public:
    inline virtual ~IObserver() = 0;
    inline virtual void update(const T &t) = 0;
};

template <typename T> class ISubject
{
  public:
    inline virtual ~ISubject() = 0;

    inline virtual void attach(const std::shared_ptr<IObserver<T>> &observer) = 0;
    inline virtual void detach(const std::shared_ptr<IObserver<T>> &observer) = 0;
    inline virtual void notify() = 0;
};

template <typename T> IObserver<T>::~IObserver() = default;

template <typename T> ISubject<T>::~ISubject() = default;

} // namespace echo::core::interfaces::patterns

#endif // ECHO_CORE_OBSERVER_HPP