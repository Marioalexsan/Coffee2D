#pragma once

////////////////////////////////////////////////////////////
// Identify the operating system
// see https://sourceforge.net/p/predef/wiki/Home/
////////////////////////////////////////////////////////////
#if defined(_WIN32)

// Windows
#define COFFEE2D_SYSTEM_WINDOWS
#ifndef NOMINMAX
#define NOMINMAX
#endif

#elif defined(__unix__)

// UNIX system, see which one it is
#if defined(__linux__)

// Linux
#define COFFEE2D_SYSTEM_LINUX

#else

// Unsupported UNIX system
#error This UNIX operating system is not supported by COFFEE2D library

#endif

#else

// Unsupported system
#error This operating system is not supported by COFFEE2D library

#endif

////////////////////////////////////////////////////////////
// Define a portable debug macro
////////////////////////////////////////////////////////////
#if !defined(NDEBUG)

#define COFFEE2D_DEBUG

#endif


////////////////////////////////////////////////////////////
// Define portable API exports
////////////////////////////////////////////////////////////
#if defined(BUILD_SHARED_LIBS)

#undef COFFEE2D_STATIC

#else

#define COFFEE2D_STATIC

#endif


#if !defined(COFFEE2D_STATIC)

#if defined(COFFEE2D_SYSTEM_WINDOWS)

// Windows compilers need specific (and different) keywords for export and import
#define COFFEE2D_API_EXPORT __declspec(dllexport)
#define COFFEE2D_API_IMPORT __declspec(dllimport)

// For Visual C++ compilers, we also need to turn off this annoying C4251 warning
#ifdef _MSC_VER

#pragma warning(disable : 4251)

#endif

#else // Linux

#define COFFEE2D_API_EXPORT __attribute__((__visibility__("default")))
#define COFFEE2D_API_IMPORT __attribute__((__visibility__("default")))

#endif

#else

// Static build doesn't need import/export macros
#define COFFEE2D_API_EXPORT
#define COFFEE2D_API_IMPORT

#endif

#if defined(COFFEE2D_API_EXPORTS)

#define COFFEE2D_API COFFEE2D_API_EXPORT

#else

#define COFFEE2D_API COFFEE2D_API_IMPORT

#endif
