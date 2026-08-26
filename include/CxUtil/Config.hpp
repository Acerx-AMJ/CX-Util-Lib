#ifndef CX_UTIL_CONFIG_HPP
#define CX_UTIL_CONFIG_HPP

// Check if debugging
#ifdef NDEBUG
   #define CX_UTIL_RELEASE
#else
   #define CX_UTIL_DEBUG
#endif

// Check the C++ standard
#if __cplusplus < 202002L
   #error "CX Util library required the C++ standard to be atleast C++20."
#endif

// Version info
#define CX_UTIL_VERSION_MAJOR 1
#define CX_UTIL_VERSION_MINOR 0
#define CX_UTIL_VERSION_PATCH 0

#define CX_UTIL_VERSION 10000
#define CX_UTIL_VERSION_STRING "1.0.0"

// Platform type
#if defined(_WIN32) || defined(_WIN64)
   #define CX_UTIL_WINDOWS
#elif defined(__linux__)
   #define CX_UTIL_LINUX
#elif defined(__APPLE__)
   #define CX_UTIL_MACOS
#else
   #define CX_UTIL_UNKNOWN_OS
#endif

// Compiler type
#if defined(__clang__)
   #define CX_UTIL_CLANG
#elif defined(__GNUC__) || defined(__GNUG__)
   #define CX_UTIL_GCC
#elif defined(_MSC_VER)
   #define CX_UTIL_MSVC
#else
   #define CX_UTIL_UNKNOWN_COMPILER
#endif

#endif // CX_UTIL_CONFIG_HPP
