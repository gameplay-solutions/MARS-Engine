#pragma once

#include "Core/Layers/Layer.h"

namespace MARS
{
	class EXPORT_TYPE ImGuiLayer : private Layer
	{
	public:

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void RenderLayerUI() override;

		virtual void OnBegin() override;
		virtual void OnEnd() override;

		friend class Application;

	protected:

		float m_Time = 0.f;
		static bool bShowDebugMenu;

	private:

		ImGuiLayer();
		~ImGuiLayer();
	};
}