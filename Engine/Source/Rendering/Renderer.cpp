#include "Rendering/Renderer.h"
#include "Rendering/VertexArray.h"
#include "Rendering/OpenGL/OpenGLRenderAPI.h"
#include "Rendering/OrthoCamera.h"


inline namespace MARS
{
	void Renderer::BeginScene(OrthographicCamera& InCamera)
	{
		
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& InVertexArray)
	{
		InVertexArray->Bind();
		RenderCommands::DrawIndexed(InVertexArray);
	}

	void Renderer::Flush()
	{

	}

	RenderAPI* RenderCommands::m_RenderAPI = new OpenGLRenderAPI;

	void RenderCommands::DrawIndexed(const std::shared_ptr<VertexArray>& InVertexArray)
	{
		m_RenderAPI->DrawIndexed(InVertexArray);
	}

	void RenderCommands::Clear()
	{
		m_RenderAPI->Clear();
	}

	void RenderCommands::SetClearColor(const LinearColor& NewColor)
	{
		m_RenderAPI->SetClearColor(NewColor);
	}
}