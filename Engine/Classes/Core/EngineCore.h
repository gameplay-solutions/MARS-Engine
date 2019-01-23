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

#ifdef COMPILER_MSVC
	#define __forceinline FORCEINLINE
#elif defined(COMPILER_GCC) || defined(COMPILER_CLANG)
	#define FORCEINLINE inline __attribute__ ((always_inline))
#endif