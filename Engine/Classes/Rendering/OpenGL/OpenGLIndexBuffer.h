#pragma once

#include "Rendering/IndexBuffer.h"
#include "CoreMinimal.h"

inline namespace MARS 
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32* Indices, uint32 Size);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind();
		virtual void Unbind();
		virtual uint32 GetCount() const;

	private:

		uint32 RendererID;
		uint32 Count;
	};
}