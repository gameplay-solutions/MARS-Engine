#include "Application/Application.h"
#include "Rendering/GraphicsContext.h"
#include "Core/EventHandler.h"

namespace MARS
{

	void Application::StartEngine()
	{
		std::unique_ptr<FPlatformHandler> Handle = std::make_unique<FPlatformHandler>();
		if (Handle)
		{

		}
	}

	void Application::Clean()
	{
	}

	void Application::NewFrame()
	{

	}

	void Application::RenderDebugGUI()
	{

	}

	Application& Application::Get()
	{
		return *m_App;
	}

	void Application::InitSystems(GLFWwindow* Window, GLADloadproc LoadProc)
	{

	}

	Application* Application::m_App = nullptr;
	Application::Application()
	{
		Assert(!m_App, "Can only have a single application")
		m_App = new Application;
	}
}

