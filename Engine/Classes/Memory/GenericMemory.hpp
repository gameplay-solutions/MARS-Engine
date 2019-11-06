#pragma once

#include "CoreMinimal.h"

#define GENERIC_MEM_SWAP_SMALL_NUMBER 16

struct OutOfMemoryHandle
{
	static bool bOutOfMemory;
	static uint64 OutOfMemoryAllocSize;
	static uint64 OutOfMemoryAllocAlignment;
	static void* OutOfMemoryPool;
	static uint32 OutOfMemoryPoolSize;
};

struct GenericMemory
{
	static FORCEINLINE void* Memmove(void* Dest, const void* Src, uintptr Amt)
	{
		return ::memmove(Dest, Src, Amt);
	}

	static FORCEINLINE int32 Memcmp(const void* Dest, const void* Src, uintptr Amt)
	{
		return ::memcmp(Dest, Src, Amt);
	}

	template<typename T>
	static FORCEINLINE void* Memset(void* Dest, T Val, uintptr Amt)
	{
		T* lDest = (T*)Dest;
		uintptr lAmt = Amt / sizeof(T);
		uintptr lRemainder = Amt % sizeof(T);

		for (uintptr i = 0; i < lAmt; i++, lDest++)
		{
			Memcpy(lDest, &Val, lRemainder);
		}

		Memcpy(lDest, &Val, lRemainder);
		return Dest;
	}

	static FORCEINLINE void* Memzero(void* Dest, uintptr Amt)
	{
		return ::memset(Dest, 0, Amt);
	}

	static FORCEINLINE void* Memcpy(void* Dest, const void* Src, uintptr Amt)
	{
		return ::memcpy(Dest, Src, Amt);
	}

	static FORCEINLINE void Memswap(void* A, void* B, uintptr Size)
	{
		if (Size <= GENERIC_MEM_SWAP_SMALL_NUMBER)
		{
			SmallMemswap(A, B, Size);
		}
		else
		{
			BigMemswap(A, B, Size);
		}
	}

	template<typename T>
	static FORCEINLINE constexpr T Align(const T Ptr, uintptr Alignment)
	{
		return (T)(((intptr_t)Ptr + Alignment - 1) & ~(Alignment - 1));
	}

	static void* Malloc(uintptr Amt, uint32 Alignment);
	static void* Realloc(void* Ptr, uintptr Amt, uint32 Alignment);
	static void* Free(void* Ptr);
	static uintptr GetAllocSize(void* Ptr);

private:

	static void SmallMemswap(void* A, void* B, uintptr Size)
	{
		Check(Size <= GENERIC_MEM_SWAP_SMALL_NUMBER);
		CHAR lData[GENERIC_MEM_SWAP_SMALL_NUMBER];
		auto* lL = (void*)&lData;
		GenericMemory::Memcpy(lL, A, Size);
		GenericMemory::Memcpy(A, B, Size);
		GenericMemory::Memcpy(B, lL, Size);
	}

	static void BigMemswap(void* A, void* B, uintptr Size);
};

template<>
FORCEINLINE void* GenericMemory::Memset(void* Dest, uint8 Val, uintptr Amt)
{
	return ::memset(Dest, Val, Amt);
}