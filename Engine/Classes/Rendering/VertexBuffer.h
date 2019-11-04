#pragma once

#include "CoreMinimal.h"

inline namespace MARS
{
	class BufferLayout;

	class VertexBuffer
	{
	public:

		VertexBuffer() = default;
		VertexBuffer(float* Verts, uint32 Size){}
		virtual ~VertexBuffer(){}
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void SetLayout(const BufferLayout& Layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(float* Verts, uint32 Size);
	};
}