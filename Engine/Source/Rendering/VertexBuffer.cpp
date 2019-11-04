#include "Rendering/VertexBuffer.h"
#include "Rendering/Renderer.h"
#include "Rendering/OpenGL/OpenGLVertexBuffer.h"

using  namespace MARS;

VertexBuffer* VertexBuffer::Create(float* Verts, uint32 Size)
{
	switch (Renderer::GetAPI())
	{
		case GraphicsAPI::None: Log::Get(LogGraphics).Fatal("Must have a Rendering API dummy!");
		case GraphicsAPI::OpenGL: return new OpenGLVertexBuffer(Verts, Size);

		default: Log::Get(LogGraphics).Fatal("Pick your god damn API");
	}

	return nullptr;
}
