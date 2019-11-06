#pragma once

#include "Core/Layers/Layer.h"

inline namespace MARS
{
	class ImGuiLayer : public Layer
	{
	public:

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void RenderLayerUI(bool* bRender) override;

		virtual void OnBegin() override;
		virtual void OnEnd() override;

	protected:

		ImGuiLayer(const String& InWindowName);
		~ImGuiLayer();

		static bool bShowDemoWindow;

	private:

		friend class Application;
		float m_Time = 0.f;

	};
}