#include "Rendering/OpenGL/OpenGLRenderAPI.h"
#include "glad/glad.h"
#include "Rendering/VertexArray.h"

void OpenGLRenderAPI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderAPI::SetClearColor(const LinearColor& NewColor)
{
	glClearColor(NewColor.R, NewColor.G, NewColor.B, NewColor.A);
}

void OpenGLRenderAPI::DrawIndexed(const std::shared_ptr<VertexArray>& InVertexArray)
{
	glDrawElements(GL_TRIANGLES, InVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}