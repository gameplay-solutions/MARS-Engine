#pragma once

#include "CoreMinimal.h"
#include "../VertexArray.h"

inline namespace MARS
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
	
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();
	
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& InBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& InBuffer) override;
		virtual Array<std::shared_ptr<VertexBuffer>> GetVertexBuffer() const override;
		virtual std::shared_ptr<IndexBuffer> GetIndexBuffer() const override;
	
	private:
	
		uint32 m_RendererID;
		Array<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
}