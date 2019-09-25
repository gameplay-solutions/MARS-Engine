#pragma once

#include "Core/EngineCore.h"
#include "Core/Layers/Layer.h"
#include "Core/Events/MouseEvent.h"
#include "Core/Events/KeyEvent.h"
#include "Core/Events/ApplicationEvent.h"

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
		bool bGL3Init = false;

	};
}