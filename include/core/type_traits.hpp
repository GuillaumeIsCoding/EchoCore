#pragma once
#ifndef ECHO_CORE_TYPE_TRAITS_HPP
#define ECHO_CORE_TYPE_TRAITS_HPP

#include <type_traits>

namespace echo::core
{

template <typename T, typename = void> struct is_container : std::false_type
{
};

template <typename T>
struct is_container<T, std::void_t<decltype(std::declval<T>().begin()), decltype(std::declval<T>().end()),
                                   decltype(std::declval<T>().size()), decltype(std::declval<T>().empty()),
                                   decltype(std::declval<T>().push_back(std::declval<typename T::value_type>()))>>
    : std::true_type
{
};

template <typename T> inline constexpr bool is_container_v = is_container<T>::value;

} // namespace echo::core

#endif // ECHO_CORE_TYPE_TRAITS_HPP