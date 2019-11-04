#include "Rendering/IndexBuffer.h"
#include "Rendering/Renderer.h"
#include "Rendering/OpenGL/OpenGLIndexBuffer.h"

using  namespace MARS;

IndexBuffer* IndexBuffer::Create(uint32* Indices, uint32 Size)
{
	switch (Renderer::GetAPI())
	{
		case GraphicsAPI::None: Log::Get(LogGraphics).Fatal(TEXT("You must select a valid Rendering API, None is not a valid API")); break;
		case GraphicsAPI::OpenGL: return new OpenGLIndexBuffer(Indices, Size); break;

		default: Log::Get(LogGraphics).Fatal(TEXT("Pick your god damn API"));
	}

	return nullptr;
}

