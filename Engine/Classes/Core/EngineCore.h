#pragma once

#include <iostream>
#include <iomanip>

#include "Types/String.hpp"
#include "Types/Array.hpp"
#include "Types/CoreTypes.h"
#include "Core/Asserts.h"
#include "Utility/Logging.h"
#include "Platform/Windows/Windows_PlatformHandler.h"

#pragma warning(push)
#pragma warning(disable:4201)
#include "glm/glm.hpp"
#pragma warning(pop)


#if defined(WIN32) || defined(__WIN32) || defined(__WIN32__) || defined(WIN64) || defined(__WIN64)
#define PLATFORM_WINDOWS 1
#elif defined(__linux__)
#define PLATFORM_LINUX 1
#else
#define PLATFORM_OTHER
#endif

#ifdef COMPILER_MSVC
	#define __forceinline FORCEINLINE
#elif defined(COMPILER_GCC) || defined(COMPILER_CLANG)
	#define FORCEINLINE inline __attribute__ ((always_inline))
#endif

#define FORCEINLINE __forceinline

#ifdef MARS_PLATFORM_WINDOWS
	#ifdef BUILD_DLL
		#define EXPORT_TYPE __declspec(dllexport)
	#else
		#define EXPORT_TYPE __declspec(dllexport)
	#endif
#endif

#if PLATFORM_WINDOWS
using FPlatformHandler = MARS::FWindows_PlatformHandler;
#elif PLATFORM_LINUX
#endif