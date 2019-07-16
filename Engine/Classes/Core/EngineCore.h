#pragma once

#if defined(WIN32) || defined(__WIN32) || defined(__WIN32__) || defined(WIN64) || defined(__WIN64)
#define PLATFORM_WINDOWS
#elif defined(__linux__)
#define PLATFORM_LINUX
#endif

#if defined(PLATFORM_WINDOWS)
	#define FORCEINLINE __forceinline
#elif defined(COMPILER_GCC) || defined(COMPILER_CLANG)
	#define FORCEINLINE inline __attribute__ ((always_inline))
#endif

#ifdef PLATFORM_WINDOWS
#define PLATFORM_NAME "Windows"
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

#ifdef PLATFORM_WINDOWS

#include <SDKDDKVer.h>
#include <windows.h>

#ifndef PLATFORM_WINSTORE
#include <Windows.UI.Core.h>
#endif

#if __has_include("vulkan/vulkan.h")
#define VULKAN_API
#endif

#include <DirectXMath.h>
#include <DirectXPackedVector.h>
using namespace DirectX;
using namespace DirectX::PackedVector;

#define ALIGN_16 void* operator new(size_t In){return _mm_malloc(In, 16);} void operator delete(void* Ptr){_mm_free(Ptr);}
#define SAFE_RELEASE(A) if((A)!=nullptr){(A)->Release();(A)=nullptr;}
#define SAFE_DELETE(A) if((A)!=nullptr){delete (A);(A)=nullptr;}
#define SAFE_DELETE_ARRAY(A) if((A)!=nullptr){delete[](A);(A)=nullptr;}
#define GFX_STRUCT struct alignas(16)
#define GFX_CLASS class alignas(16)

template <typename T>
inline void SwapPtr(T*& A, T*& B)
{
	T* swap = A;
	A = B;
	B = swap;
}

template<typename T>
inline void Recreate(T*& Obj)
{
	SAFE_DELETE(Obj);
	Obj = new T;
}

static const XMFLOAT4X4 IDENTITYMATRIX = XMFLOAT4X4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
#endif

#include "MARSPCH.h"