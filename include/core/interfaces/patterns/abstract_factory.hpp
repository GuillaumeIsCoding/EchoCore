#pragma once
#ifndef ECHO_CORE_ABSTRACT_FACTORY_HPP
#define ECHO_CORE_ABSTRACT_FACTORY_HPP

#include "core/macros/export.hpp"

#include <memory>

namespace echo::core::interfaces::patterns
{

template <typename T> class IAbstractFactory
{
  public:
    inline virtual ~IAbstractFactory() = 0;

    inline virtual std::unique_ptr<T> create_unique() = 0;
    inline virtual std::shared_ptr<T> create_shared() = 0;
};

template <typename T> IAbstractFactory<T>::~IAbstractFactory() = default;

} // namespace echo::core::interfaces::patterns

#endif // ECHO_CORE_ABSTRACT_FACTORY_HPP