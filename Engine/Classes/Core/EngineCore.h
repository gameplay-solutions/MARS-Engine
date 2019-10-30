#pragma once

// @todo(chrisr): rewrite and clean up this header. I don't even know why the event macros are in here wtf

inline namespace MARS
{
	template<typename T>
	constexpr auto BIT(T x) { return 1 << x; }
	#define BIT(x) BIT(x) // here to trick false errors on dumb compilers (cough MSVC)
	
	/** @note(chrisr): Will eventually have this be a custom delegate system. I have a personal hatred of std::bind && std::placeholders */
	#define BIND_EVENT(Func) std::bind(&Func, this)
	#define BIND_EVENT_ONE_PARAM(Func) std::bind(&Func, this, std::placeholders::_1)
	#define BIND_EVENT_TWO_PARAM(Func) std::bind(&Func, this, std::placeholders::_2)
	#define BIND_EVENT_THREE_PARAM(Func) std::bind(&Func, this, std::placeholders::_3)
	#define BIND_EVENT_FOUR_PARAM(Func) std::bind(&Func, this, std::placeholders::_4)
	#define BIND_EVENT_FIVE_PARAM(Func) std::bind(&Func, this, std::placeholders::_5)
	#define BIND_EVENT_SIX_PARAM(Func) std::bind(&Func, this, std::placeholders::_6)
} using namespace MARS; // a lot of this will be cleaned up when the MARS Header Tool gets written. For now, we just have to deal with hacky code smell

#if defined(WIN32) || defined(__WIN32) || defined(__WIN32__) || defined(WIN64) || defined(__WIN64)
#define PLATFORM_WINDOWS 1
#elif defined(__linux__)
#define PLATFORM_LINUX 1
#endif

#if PLATFORM_WINDOWS
#include <Windows.h>
#endif

#if defined(PLATFORM_WINDOWS)
	#define FORCEINLINE __forceinline
#elif defined(COMPILER_GCC) || defined(COMPILER_CLANG)
	#define FORCEINLINE inline __attribute__ ((always_inline))
#endif

#ifdef MARS_EXPORTS
	#define EXPORT_TYPE
#else
	#define EXPORT_TYPE
#endif

#include "MARSPCH.h"