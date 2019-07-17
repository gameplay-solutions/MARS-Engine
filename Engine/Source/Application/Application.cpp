#include "Application/Application.h"
#include "Core/Layers/Layer.h"
#include "glad/glad.h"
#include "Input/InputHandler.h"

namespace MARS
{
	Application* Application::Instance = nullptr;

	Application::Application()
	{
		Instance = this;

		WindowPtr = std::unique_ptr<Window>(Window::Create());
		bRunning = true;

		WindowPtr->SetEventCallback(BIND_EVENT_ONE_PARAM(Application::OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::InitMARS()
	{
		Log::Get(LogInit).Info("MARS has started");
		Run();
	}

	void Application::Run()
	{
		while (bRunning)
		{
			glClearColor(0.1, 0.1, 0.1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (auto* It : m_LayerStack)
			{
				It->OnUpdate();
			}

			auto[x, y] = Input::GetMousePos();

			WindowPtr->OnUpdate();
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

		// Log::Get(LogTemp).Info("{}", e.ToString());
	}

	void Application::PushLayer(Layer* InLayer)
	{
		m_LayerStack.PushLayer(InLayer);
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