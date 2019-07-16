#pragma once

#if defined(WIN32) || defined(__WIN32) || defined(__WIN32__) || defined(WIN64) || defined(__WIN64)
#define PLATFORM_WINDOWS
#elif defined(__linux__)
#define PLATFORM_LINUX
#endif

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
#endif

#if defined(PLATFORM_WINDOWS)
	#define FORCEINLINE __forceinline
#elif defined(COMPILER_GCC) || defined(COMPILER_CLANG)
	#define FORCEINLINE inline __attribute__ ((always_inline))
#endif

#ifdef MARS_EXPORTS
	#define EXPORT_TYPE __declspec(dllexport)
#else
	#define EXPORT_TYPE __declspec(dllimport)
#endif

template<typename T>
constexpr auto BIT(T x) { return 1 << x; }

#define BIT(x) BIT(x)

#define BIND_EVENT(Func) std::bind(&Func, this)
#define BIND_EVENT_ONE_PARAM(Func) std::bind(&Func, this, std::placeholders::_1)
#define BIND_EVENT_TWO_PARAM(Func) std::bind(&Func, this, std::placeholders::_2)
#define BIND_EVENT_THREE_PARAM(Func) std::bind(&Func, this, std::placeholders::_3)
#define BIND_EVENT_FOUR_PARAM(Func) std::bind(&Func, this, std::placeholders::_4)
#define BIND_EVENT_FIVE_PARAM(Func) std::bind(&Func, this, std::placeholders::_5)
#define BIND_EVENT_SIX_PARAM(Func) std::bind(&Func, this, std::placeholders::_6)

#include "MARSPCH.h"