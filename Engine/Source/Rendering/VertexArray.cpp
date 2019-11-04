#include "Rendering/VertexArray.h"
#include "Rendering/Renderer.h"
#include "Rendering/OpenGL/OpenGLVertexArray.h"

VertexArray* VertexArray::Create()
{
	switch (Renderer::GetAPI())
	{
		case GraphicsAPI::None: Log::Get(LogError).Fatal(TEXT("unsupported rendering API {}"), (uint8)GraphicsAPI::None); return nullptr;
		case GraphicsAPI::OpenGL: return new OpenGLVertexArray();
	}

	return nullptr;
}
