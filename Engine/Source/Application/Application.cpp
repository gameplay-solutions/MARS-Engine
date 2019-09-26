#include "Application/Application.h"
#include "glad/glad.h"
#include "Input/InputHandler.h"
#include "UserInterface/ImGuiLayer.h"

namespace MARS
{
	Application* Application::Instance = nullptr;

	Application::Application()
	{
		bRunning = true;
		Instance = this;
		WindowPtr = std::unique_ptr<Window>(Window::Create());
		WindowPtr->SetEventCallback(BIND_EVENT_ONE_PARAM(Application::OnEvent));

		ImGuiLayerPtr = new ImGuiLayer;
		PushOverlay(ImGuiLayerPtr);
	}

	Application::~Application()
	{

	}

	void Application::InitMARS()
	{
		Log::Get(LogInit).Info("MARS Pre-Init Completed with 0 errors."); // TODO update this when the error log is written.
		Run();
	}

	void Application::Run()
	{
		while (bRunning)
		{
			glClearColor(0.1, 0.1, 0.1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			ImGuiLayerPtr->OnBegin();
			for (auto* Element : m_LayerStack) 
			{
				/*Element->OnUpdate();*/
				Element->RenderLayerUI();
			}
			ImGuiLayerPtr->OnEnd();


			WindowPtr->Refresh();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher _Dispatcher(e);
		_Dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_ONE_PARAM(Application::OnWindowClose));

		for (auto It = m_LayerStack.end(); It != m_LayerStack.begin();)
		{
			(*--It)->OnEvent(e);
			if (e.IsEventHandled())
			{
				break;
			}
		}
	}

	void Application::PushLayer(Layer* InLayer)
	{
		m_LayerStack.PushElement(InLayer);
		InLayer->OnAttach();
	}

	void Application::PushOverlay(Layer* InOverlay)
	{
		m_LayerStack.PushOverlay(InOverlay);
		InOverlay->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		e;

		bRunning = false;
		return true;
	}
}