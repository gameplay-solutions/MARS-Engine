#pragma once

#include "EngineCore.h"

#define Assertf(x, ...)\
{\
	if (!(x))\
	{\
		Log::Get(LogError).Fatal("Assertion Failed: {}", __VA_ARGS__);\
		PLATFORM_DEBUG_BREAK();\
		CA_ASSUME(false);\
	}\
};

#define Assert(x)\
{\
	if (!(x))\
	{\
		PLATFORM_DEBUG_BREAK();\
		CA_ASSUME(false);\
	}\
};


#define Check(x) Assert(x) // Honestly, this is here cause I have a heavy UE4 background
#define NoEntry() Assert(!"This should never be called")
#define Unimplemented() Assert(!"Function requires implementation")