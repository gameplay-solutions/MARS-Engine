#pragma once

#include "CoreMinimal.h"
#include "Rendering/VertexBuffer.h"
#include "../BufferLayout.h"

inline namespace MARS
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:

		OpenGLVertexBuffer() = default;

		OpenGLVertexBuffer(float* Verts, uint32 Size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;


		virtual inline void SetLayout(const BufferLayout& Layout) override;
		virtual inline const BufferLayout& GetLayout() const override;

	private:

		uint32 m_RendererID;
		BufferLayout m_Layout;
	};
}