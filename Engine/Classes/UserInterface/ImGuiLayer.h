#pragma once

#include "Core/Layers/Layer.h"

namespace MARS
{
	class EXPORT_TYPE ImGuiLayer : public Layer
	{
	public:

		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void RenderLayerUI() override;

		virtual void OnBegin() override;
		virtual void OnEnd() override;

	protected:
		float m_Time = 0.f;
	};
}