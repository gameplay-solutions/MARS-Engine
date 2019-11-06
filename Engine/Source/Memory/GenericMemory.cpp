#include "Memory/GenericMemory.hpp"

void* GenericMemory::Malloc(uintptr Amt, uint32 Alignment)
{
	Alignment = Math::Max(Amt >= 16 ? 16u : 8u, Alignment);
	auto* Ptr = ::malloc(Amt + Alignment + sizeof(void*) + sizeof(uintptr));
	auto* Result = Align((uint8*)Ptr + sizeof(void*) + sizeof(uintptr), (uintptr)Alignment);
	*((void**)((uint8*)Result - sizeof(void*))) = Ptr;
	*((uintptr*)((uint8*)Result - sizeof(void*) - sizeof(uintptr))) = Amt;
	return Result;
}

void* GenericMemory::Realloc(void* Ptr, uintptr Amt, uint32 Alignment)
{
	Alignment = Math::Max(Amt >= 16 ? 16u : 8u, Alignment);

	if (Ptr == nullptr)
	{
		return GenericMemory::Malloc(Amt, Alignment);
	}

	if (Amt == 0)
	{
		GenericMemory::Free(Ptr);
		return nullptr;
	}

	void* Result = Malloc(Amt, Alignment);
	uintptr Size = GenericMemory::GetAllocSize(Ptr);
	GenericMemory::Memcpy(Result, Ptr, Math::Min(Size, Amt));
	Free(Ptr);

	return Result;
}

void* GenericMemory::Free(void* Ptr)
{
	if (Ptr)
	{
		::free(*((void**)((uint8*)Ptr - sizeof(void*))));
	}

	return nullptr;
}

uintptr GenericMemory::GetAllocSize(void* Ptr)
{
	return *((uintptr*)((uint8*)Ptr - sizeof(void*) - sizeof(uintptr)));
}

void GenericMemory::BigMemswap(void* A, void* B, uintptr Size)
{
	auto* lPtr1 = (uint64*)A;
	auto* lPtr2	= (uint64*)B;
	while (Size > GENERIC_MEM_SWAP_SMALL_NUMBER)
	{
		uint64 lTemp = *lPtr1;
		*lPtr1 = *lPtr2;
		*lPtr2 = lTemp;
		Size -= 8;
		lPtr1++;
		lPtr2++;
	}
	SmallMemswap(lPtr1, lPtr2, Size);
}

