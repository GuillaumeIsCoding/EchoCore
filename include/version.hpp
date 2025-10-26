#pragma once
#ifndef ECHO_CORE_VERSION_HPP
#define ECHO_CORE_VERSION_HPP

#define ECHO_CORE_VERSION_MAJOR 0

#define ECHO_CORE_VERSION_MINOR 0

#define ECHO_CORE_VERSION_PATCH 1

#define ECHO_CORE_TO_VERSION(major, minor, patch) (major * 10000 + minor * 100 + patch)
#define ECHO_CORE_VERSION                                                                                              \
    ECHO_CORE_TO_VERSION(ECHO_CORE_VERSION_MAJOR, ECHO_CORE_VERSION_MINOR, ECHO_CORE_VERSION_PATCH)

#endif // ECHO_CORE_VERSION_HPP