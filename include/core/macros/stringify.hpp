#pragma once
#ifndef ECHO_CORE_STRINGIFY_HPP
#define ECHO_CORE_STRINGIFY_HPP

#include <string>

#ifndef ECHO_STRINGIFY

#define ECHO__STRINGIFY(x) #x
#define ECHO_STRINGIFY(x) ECHO__STRINGIFY(x)

#endif // ECHO_STRINGIFY

#ifndef ECHO_STRINGIFY_PTR

#define ECHO__STRINGIFY_PTR(x) std::to_string(reinterpret_cast<uintptr_t>(x))
#define ECHO_STRINGIFY_PTR(x) ECHO__STRINGIFY_PTR(x)

#endif // ECHO_STRINGIFY_PTR

#endif // ECHO_CORE_STRINGIFY_HPP