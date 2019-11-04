#pragma once

#include "CoreMinimal.h"
#include "..\RenderTypes.h"
#include "..\RenderAPI.h"

inline namespace MARS
{
	class VertexArray;

	class OpenGLRenderAPI : public RenderAPI
	{
	public:

		virtual void Clear() override;
		virtual void SetClearColor(const LinearColor& NewColor) override;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& InVertexArray) override;

	};
}