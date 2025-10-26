#pragma once
#ifndef ECHO_CORE_EXPORT_COMMON_HPP
#define ECHO_CORE_EXPORT_COMMON_HPP

#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) ||                  \
    defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define ECHO_CORE_DECL_EXPORT __declspec(dllexport)
#define ECHO_CORE_DECL_IMPORT __declspec(dllimport)
#elif __GNUG__ >= 4
#define ECHO_CORE_DECL_EXPORT __attribute__((visibility("default")))
#define ECHO_CORE_DECL_IMPORT __attribute__((visibility("default")))
#define ECHO_CORE_DECL_HIDDEN __attribute__((visibility("hidden")))
#else
#define ECHO_CORE_DECL_EXPORT
#define ECHO_CORE_DECL_IMPORT
#endif

#ifndef ECHO_CORE_DECL_HIDDEN
#define ECHO_CORE_DECL_HIDDEN
#endif

#endif // ECHO_CORE_EXPORT_COMMON_HPP