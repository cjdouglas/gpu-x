#pragma once

#if defined __GPUX_PLATFORM_AMD__ && defined __GPUX_PLATFORM_NVIDIA__
#error only one of __GPUX_PLATFORM_AMD__ and __GPUX_PLATFORM_NVIDIA__ can be defined!
#elif !defined __GPUX_PLATFORM_AMD__ && !defined __GPUX_PLATFORM_NVIDIA__
#error none of  __GPUX_PLATFORM_AMD__ or __GPUX_PLATFORM_NVIDIA__ are defined!
#endif

#if defined(_WIN32) || defined(_WIN64)
#ifdef GPUX_BUILD_SHARED
#define GPUX_API __declspec(dllexport)
#elif defined(BUILD_SHARED_LIBS)
#define GPUX_API __declspec(dllimport)
#else  // not _WIN32 or _WIN64, no __declspec needed
#define GPUX_API
#endif
#else
#define GPUX_API
#endif
