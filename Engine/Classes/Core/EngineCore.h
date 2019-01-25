#pragma once

#include <iostream>
#include <iomanip>

#include "Types/String.hpp"
#include "Types/Array.hpp"
#include "Types/CoreTypes.h"
#include "Core/Asserts.h"
#include "Utility/Logging.h"

#pragma warning(push)
#pragma warning(disable:4201)
#include "glm/glm.hpp"
#pragma warning(pop)


#if defined(WIN32) || defined(__WIN32) || defined(__WIN32__) || defined(WIN64) || defined(__WIN64)
#define PLATFORM_WINDOWS 1
#elif defined(__linux__)
#define PLATFORM_LINUX 1
#endif

#ifdef COMPILER_MSVC
	#define FORCEINLINE __forceinline
#elif defined(COMPILER_GCC) || defined(COMPILER_CLANG)
	#define FORCEINLINE inline __attribute__ ((always_inline))
#endif

#if PLATFORM_WINDOWS
#define PLATFORM_NAME "Windows"
#endif

#ifdef BUILD_DLL
	#define EXPORT_TYPE __declspec(dllexport)
#else
	#define EXPORT_TYPE __declspec(dllimport)
#endif