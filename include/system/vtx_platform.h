#ifndef VTX_PLATFORM_H
#define VTX_PLATFORM_H

#define VTX_NONCLIENT_BUILD

#ifdef _WIN32
#define VTX_SYS_WINDOWS

#ifndef NOMINMAX
#define NOMINMAX
#endif
#elif defined (__linux__)
#define VTX_SYS_LINUX
#elif defined (__APPLE__)
#define VTX_SYS_MACOS
#endif
#ifndef VTX_STATIC_BUILD
#ifdef VTX_SYS_WINDOWS
#ifdef VTX_NONCLIENT_BUILD
#define VTX_API __declspec(dllexport)
#else
#define VTX_API __declspec(dllimport)
#endif

//Visual c++ compiler warning C4251 disable
#ifdef _MSC_VER
#pragma warning(disable : 4251)
#endif
#else
#ifdef __GNUC__ >= 4
#define VTX_API __attribute__ ((__visibility__("default")))
#else
#define VTX_API VTX_API
#endif
#endif
#else
#define VTX_API VTX_API
#endif
#endif