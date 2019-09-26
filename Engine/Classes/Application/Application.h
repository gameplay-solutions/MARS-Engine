#pragma once

#include "Core/EngineCore.h"
#include "Application/Window.h"
#include "Core/Events/ApplicationEvent.h"

namespace MARS
{
	class Layer;
	class ImGuiLayer;

	class EXPORT_TYPE Application
	{
	public:

		Application();
		virtual ~Application();

		/** 
		 *	Global init function. Called by the application.
		 *	Starts the main loop and creates the Window class.
		 *	This is the first init function call of the engine
		 *	so it's a bad idea to try and add code here, 
		 *	it will most likely rely on system that haven't been initialized yet.
		 **/
		void InitMARS();

		void OnEvent(Event& e);

		void PushLayer(Layer* InLayer);
		void PushOverlay(Layer* InOverlay);

		inline Window& GetWindow() { return *WindowPtr; }
		inline static Application& Get() { return *Instance; }

	private:

		void Run();

		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> WindowPtr;
		bool bRunning = false;
		MStack<Layer> m_LayerStack;
		static Application* Instance;
		ImGuiLayer* ImGuiLayerPtr;
	};

	Application* CreateApplication();
}