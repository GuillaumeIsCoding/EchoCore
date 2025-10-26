#pragma once
#ifndef ECHO_CORE_EXPORT_HPP
#define ECHO_CORE_EXPORT_HPP

#include "core/macros/export_common.hpp"

#ifdef ECHO_CORE_BUILDING_SHARED
#define ECHO_CORE_EXPORT ECHO_CORE_DECL_EXPORT
#elif defined(ECHO_CORE_LINKING_SHARED)
#define ECHO_CORE_EXPORT ECHO_CORE_DECL_IMPORT
#endif

// Building library archive (static)
#ifndef ECHO_CORE_EXPORT
#define ECHO_CORE_EXPORT
#endif

#endif // ECHO_CORE_EXPORT_HPP