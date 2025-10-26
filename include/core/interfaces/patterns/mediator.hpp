#pragma once
#ifndef ECHO_CORE_MEDIATOR_HPP
#define ECHO_CORE_MEDIATOR_HPP

#include "core/macros/export.hpp"

#include "types.hpp"

#include <memory>

namespace echo::core::interfaces::patterns
{

template <typename T> class IMediator
{
  public:
    using Event = uint64;

    inline virtual ~IMediator() = 0;
    inline virtual notify(const std::shared_ptr<T> &sender, const Event &event = 0) = 0;
};

template <typename T> IMediator<T>::~IMediator() = default;

} // namespace echo::core::interfaces::patterns

#endif // ECHO_CORE_MEDIATOR_HPP