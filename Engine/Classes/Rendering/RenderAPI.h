#pragma once

#include "CoreMinimal.h"
#include "Rendering/RenderTypes.h"

inline namespace MARS
{
	class VertexArray;

	class RenderAPI
	{
	public:

		virtual void Clear() = 0;
		virtual void SetClearColor(const LinearColor& NewColor) = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& InVertexArray) = 0;

		FORCEINLINE static GraphicsAPI GetAPI() { return CurrentAPI; }

	private:

		static GraphicsAPI CurrentAPI;
	};
}