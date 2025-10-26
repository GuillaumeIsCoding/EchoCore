#pragma once
#ifndef ECHO_CORE_PLATFORM_DETECTION_HPP
#define ECHO_CORE_PLATFORM_DETECTION_HPP

#ifdef _WIN32

/* Windows x64/x86 */
#ifdef _WIN64

/* Windows x64  */
#define ECHO_PLATFORM_WINDOWS

#else

/* Windows x86 */
#error "x86 Builds are not supported!"

#endif // _WIN64

#elif defined(__APPLE___) || defined(__MACH__)
#include <TargetConditionals.h>

#if TARGET_IPHONE_SIMULATOR == 1

#error "IOS simulator is not supported!"

#elif TARGET_OS_IPHONE == 1

#define ECHO_PLATFORM_IOS
#error "IOS is not supported!"

#elif TARGET_OS_MAC == 1

#define ECHO_PLATFORM_MACOS
#error "MacOS is not supported!"

#else

#error "Unknown Apple platform!"

#endif // TARGET_IPHONE_SIMULATOR

#elif defined(__ANDROID__)

#define ECHO_PLATFORM_ANDROID
#error "Android is not supported!"

#elif defined(__linux__)

#define ECHO_PLATFORM_LINUX

#else

/* Unknown compiler/platform */
#error "Unknown platform!"

#endif // _WIN32

#endif // ECHO_CORE_PLATFORM_DETECTION_HPP