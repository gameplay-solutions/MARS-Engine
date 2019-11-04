#pragma once

#include "CoreMinimal.h"

/** @TODO(Chrisr): Implement custom Array function */
// @TEMPHACK: The Array class won't use std::vector
#include <vector>

template<typename ElementType/*, typename Allocator*/>
class Array : public std::vector<ElementType>
{
	template<typename OtherElementType/*, typename OtherAllocator*/>
	friend class Array;
	
public:

	Array<ElementType>() : std::vector<ElementType>(){}
	Array<ElementType>(size_t n) : std::vector<ElementType>(n){}

	FORCEINLINE int32 Num() const
	{
		return size();
	}
};