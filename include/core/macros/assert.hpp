#pragma once
#ifndef ECHO_CORE_ASSERT_HPP
#define ECHO_CORE_ASSERT_HPP

#include "core/macros/utils.hpp"

#include "core/macros/logging.hpp"

#include "core/macros/stringify.hpp"

#include <filesystem>

#ifdef ECHO_ENABLE_ASSERTS

#define ECHO_INTERNAL_ASSERT_IMPL(type, check, msg, ...)                                                               \
    {                                                                                                                  \
        if (!(check))                                                                                                  \
        {                                                                                                              \
            ECHO##type##ERROR(msg, __VA_ARGS__);                                                                       \
            ECHO_DEBUG_BREAK();                                                                                        \
        }                                                                                                              \
    }

#define ECHO_INTERNAL_ASSERT_WITH_MSG(type, check, ...)                                                                \
    ECHO_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)

#define ECHO_INTERNAL_ASSERT_NO_MSG(type, check)                                                                       \
    ECHO_INTERNAL_ASSERT_IMPL(type check, "Assertion '{0}' failed at {1}:{2}", ECHO_STRINGIFY(check),                  \
                              std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define ECHO_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro

#define ECHO_INTERNAL_ASSERT_GET_MACRO(...)                                                                            \
    ECHO_EXPAND_MACRO(                                                                                                 \
        ECHO_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, ECHO_INTERNAL_ASSERT_WITH_MSG, ECHO_INTERNAL_ASSERT_NO_MSG))

#else

#define ECHO_CLIENT_ASSERT(...) ECHO_EXPAND_MACRO(ECHO_INTERNAL_ASSERT_GET_MACROS(__VA_ARGS__)(_CLIENT_, __VA_ARGS__))
#define ECHO_CORE_ASSERT(...) ECHO_EXPAND_MACRO(ECHO_INTERNAL_ASSERT_GET_MACROS(__VA_ARGS__)(_CORE_, __VA_ARGS__))

#endif // ECHO_ENABLE_ASSERTS

#endif // ECHO_CORE_ASSERT_HPP