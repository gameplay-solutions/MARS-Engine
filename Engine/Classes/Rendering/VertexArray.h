#pragma once

#include "CoreMinimal.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

inline namespace MARS
{
	class VertexArray
	{
	public:
	
		virtual ~VertexArray() { }
	
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	
		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& InBuffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& InBuffer) = 0;
	
		virtual Array<std::shared_ptr<VertexBuffer>> GetVertexBuffer() const = 0;
		virtual std::shared_ptr<IndexBuffer> GetIndexBuffer() const = 0;
	
		static VertexArray* Create();
	};
}