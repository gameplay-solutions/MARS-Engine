#pragma once

#include "CoreMinimal.h"

template<typename T>
class MSmartPtr
{
public:

	explicit MSmartPtr(T* Pointee) : Pointee_(Pointee){ }
	~MSmartPtr() { }
	
	MSmartPtr& operator=(const MSmartPtr& Other)
	{
		if (this != &Other)
		{
			delete Pointee_;
			Pointee_ = Other.Pointee_;
			Other.Pointee_ = 0;
		}

		return *this;
	}

	T** operator&()
	{
		return &Pointee_;
	}

	T& operator*() const
	{
		return *Pointee_;
	}

	T* operator->() const
	{
		return Pointee_;
	}

private:

	T* Pointee_;
};
