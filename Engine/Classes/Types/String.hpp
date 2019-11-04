#pragma once

#include "Types/CoreTypes.hpp"

/** @TODO(Chrisr): Implement custom String class */
// @TEMPHACK: The string class won't use std::string
#include <string>
#include "Array.hpp"
using String = std::string;

class MString
{
 	using DataType = Array<CHAR>;
 	using Data = DataType;

public:

	void Add(const CHAR* InStr)
	{
		
	}

	void Add(const CHAR& InStr)
	{

	}

	void Add(CHAR&& InStr)
	{

	}
};