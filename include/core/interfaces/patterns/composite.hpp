#pragma once
#ifndef ECHO_CORE_COMPOSITE_HPP
#define ECHO_CORE_COMPOSITE_HPP

#include "core/macros/export.hpp"

#include "core/interfaces/icomponent.hpp"

#include "core/type_traits.hpp"

#include <memory>

namespace echo::core::interfaces::patterns
{

template <typename C, typename = std::enable_if_t<is_container_v<C>>> class IComposite
{
  public:
    inline virtual ~IComposite() = default;

    inline virtual void add(const std::shared_ptr<IComponent> &component) = 0;
    inline virtual bool remove(const std::shared_ptr<IComponent> &component) = 0;
    inline virtual C get_children() const;
    inline virtual void execute() = 0;
};

} // namespace echo::core::interfaces::patterns

#endif // ECHO_CORE_COMPOSITE_HPP