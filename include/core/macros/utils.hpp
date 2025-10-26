#pragma once
#ifndef ECHO_CORE_UTILS_HPP
#define ECHO_CORE_UTILS_HPP

#include "core/macros/platform_detection.hpp"

#include <unordered_map>

#include <mutex>

#ifdef ECHO__DEBUG

#if defined(ECHO_PLATFORM_WINDOWS)

#define ECHO_DEBUG_BREAK() __debugbreak()

#elif defined(ECHO_PLATFORM_LINUX)

#include <signal.h>
#define ECHO_DEBUG_BREAK() raise(SIGTRAP)

#else

#error "Platform doesn't support debugbreak yet!"

#endif

#define ECHO_ENABLE_ASSERTS

#else

#define ECHO_DEBUG_BREAK()

#endif // DEBUG

#define ECHO_EXPAND_MACRO(x) x

#define ECHO_BIT(x) (1 << x)

#define ECHO_BIND_EVENT_FN(fn)                                                                                         \
    [this](auto &&...args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#include "core/macros/assert.hpp"
#include "core/macros/logging.hpp"

#endif // ECHO_CORE_UTILS_HPP
