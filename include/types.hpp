#pragma once
#ifndef ECHO_CORE_TYPES_HPP
#define ECHO_CORE_TYPES_HPP

#define S_CALLTYPE __cdecl

#ifdef __GNUC__
#if __GNUC__ < 4
#error "Decorator requires GCC 4.X"
#endif
#endif

#if defined(__LP64__) || defined(__x86_64__) || defined(_WIN64) || defined(__aarch64__) || defined(__s390x__)
#define X64BITS
#endif

#if !defined(DECORATOR_BIG_ENDIAN)
#if defined(_PS3)
#define DECORATOR_BIG_ENDIAN 1
#endif
#if defined(__GNUC__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define DECORATOR_BIG_ENDIAN 1
#endif
#endif

typedef unsigned char uint8;
typedef signed char int8;

#if defined(_WIN32) && !defined(__GNUC__)

typedef __int16 int16;
typedef unsigned __int16 uint16;
typedef __int32 int32;
typedef unsigned __int32 uint32;
typedef __int64 int64;
typedef unsigned __int64 uint64;

typedef int64 lint64;
typedef uint64 ulint64;

#ifdef X64BITS
typedef __int64 intp;           // intp is an integer that can accomodate a pointer
typedef unsigned __int64 uintp; // (ie, sizeof(intp) >= sizeof(int) && sizeof(intp) >= sizeof(void *)
#else
typedef __int32 intp;
typedef unsigned __int32 uintp;
#endif
#else // _WIN32

typedef short int16;
typedef unsigned short uint16;
typedef int int32;
typedef unsigned int uint32;
typedef long long int64;
typedef unsigned long long uint64;

typedef long int lint64;
typedef unsigned long int ulint64;

#ifdef X64BITS
typedef long long intp;
typedef unsigned long long uintp;
#else
typedef int intp;
typedef unsigned int uintp;
#endif
#endif // else _WIN32

#endif // ECHO_CORE_TYPES_HPP