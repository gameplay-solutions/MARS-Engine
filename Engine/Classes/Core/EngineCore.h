#pragma once

// @todo(chrisr): rewrite and clean up this header. I don't even know why the event macros are in here wtf

inline namespace MARS
{
	template<typename T>
	constexpr auto BIT(T x) { return 1 << x; }
	#define BIT(x) BIT(x)
	
	/** @note(chrisr): Will eventually have this be a custom delegate system. I have a personal hatred of std::bind && std::placeholders */
	#define BIND_EVENT(Func)									std::bind(&Func, this)
	#define BIND_EVENT_ONE_PARAM(Func)							std::bind(&Func, this, std::placeholders::_1)
	#define BIND_EVENT_TWO_PARAM(Func)							std::bind(&Func, this, std::placeholders::_2)
	#define BIND_EVENT_THREE_PARAM(Func)						std::bind(&Func, this, std::placeholders::_3)
	#define BIND_EVENT_FOUR_PARAM(Func)							std::bind(&Func, this, std::placeholders::_4)
	#define BIND_EVENT_FIVE_PARAM(Func)							std::bind(&Func, this, std::placeholders::_5)
	#define BIND_EVENT_SIX_PARAM(Func)							std::bind(&Func, this, std::placeholders::_6)
} // a lot of this will be cleaned up when the MARS Header Tool gets written. For now, we just have to deal with hacky code smell

#if defined(WIN32) || defined(__WIN32) || defined(__WIN32__) || defined(WIN64) || defined(__WIN64)
	#define PLATFORM_WINDOWS 1
#elif defined(__linux__)
	#define PLATFORM_LINUX 1
#endif

#if PLATFORM_WINDOWS
#include <Windows.h>
	#ifdef TEXT
		#undef TEXT
#define TEXT(x)													std::string(x)
#endif

#define PLATFORM_CODE_SECTION(x)								__declspec(code_seq(x))
#define PLATFORM_DEBUG_BREAK()									(__nop(),__debugbreak())
#define CA_ASSUME(x)											__analysis_assume(!!(x))

#endif

#if defined(PLATFORM_WINDOWS)
	#define FORCEINLINE											__forceinline
#elif defined(COMPILER_GCC) || defined(COMPILER_CLANG)
	#define FORCEinline											__attribute__ ((always_inline))
#endif

#ifdef MARS_EXPORTS
	#define EXPORT_TYPE
#else
	#define EXPORT_TYPE
#endif

#define UNUSED_PROPERTY(x) (x);

enum DEFAULT_CONSTRUCT
{
	ForceInit,
	ForceZeroInit
};

enum DO_NOT_CONSTRUCT
{
	NoInit
};

enum
{
	INDEX_NONE = -1
};

enum
{
	UNICODE_BOM = 0xfeff
};

#define DEPRECATED(Version, Message) [[deprecated(Message " Please update to newest API. Removed in ")]]

#define NO_COPY(Type)\
Type(Type&&)=delete;\
Type(const Type&)=delete;\
Type& operator=(const Type& Other)=delete;\
Type& operator=(Type& Other)=delete

#ifndef ASSUME
	#define ASSUME(...)
#endif

#ifndef LIKELY
	#if (defined(__clang__) || defined(__GNUC__))
		#define(x)					__builtin_expect(!!(x),1)
	#else
		#define LIKELY(x)			(x)
	#endif
#endif

#ifndef UNLIKELY
	#if (defined(__clang__) || defined(__GNUC__))
		#define(x)					__builtin_expect(!!(x),0)
	#else
		#define UNLIKELY(x)			(x)
	#endif
#endif

// conditional include flags
// this will be replaced by MHT, the console command line, and editor settings.
//#define USE_MARS_MATH
//#define USE_GAMEFRAMEWORK
//#define USE_STL