#pragma once

#include "CoreMinimal.h"

inline namespace MARS
{
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer(){}

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual uint32 GetCount() const = 0;

		static IndexBuffer* Create(uint32* Indices, uint32 Size);
	};
}