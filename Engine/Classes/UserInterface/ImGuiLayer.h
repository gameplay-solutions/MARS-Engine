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

		virtual void OnUpdate() override;
		virtual void OnEvent(Event& InEvent) override;
		virtual void OnAttach() override;
		virtual void OnDetach() override;

	private:

		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnKeyReleased(KeyReleasedEvent& e);
		bool OnKeyTyped(KeyTypedEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

		float m_Time = 0.f;

	};
}