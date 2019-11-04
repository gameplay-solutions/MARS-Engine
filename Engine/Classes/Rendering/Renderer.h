#pragma once

#include "CoreMinimal.h"
#include "Rendering/RenderTypes.h"
#include "RenderAPI.h"

inline namespace MARS
{
	class VertexArray;
	class OrthographicCamera;

	struct Renderer
	{
		static void BeginScene(OrthographicCamera& InCamera);
		static void EndScene();
		static void Submit(const std::shared_ptr<VertexArray>& InVertexArray);
		static void Flush();

		FORCEINLINE static GraphicsAPI GetAPI() { return RenderAPI::GetAPI(); }

	private:

	};

	class RenderCommands
	{
	public:

		static void Clear();
		static void SetClearColor(const LinearColor& NewColor);
		static void DrawIndexed(const std::shared_ptr<VertexArray>& InVertexArray);

	private:

		static RenderAPI* m_RenderAPI;
	};

}