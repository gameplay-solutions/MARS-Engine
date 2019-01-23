#pragma once

#include "Types/CoreTypes.h"

/** @TODO(Chrisr): Implement custom Array function */
// @TEMPHACK: The Array class won't use std::vector
#include <vector>

template<typename ElementType>
class Array : public std::vector<ElementType>
{
public:

	Array<ElementType>() : std::vector<ElementType>(){}
	Array<ElementType>(size_t n) : std::vector<ElementType>(n){}
};