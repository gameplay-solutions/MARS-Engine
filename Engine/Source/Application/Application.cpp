#include "Application/Application.h"
#include "Input/InputHandler.h"
#include "UserInterface/ImGuiLayer.h"
#include "Rendering/BufferLayout.h"
#include "Rendering/Renderer.h"
#include "UserInterface/OutputLog.h"
#include "Rendering/RenderTypes.h"

extern ImGuiLayer* MARS::CreateImGuiLayer();

inline namespace MARS
{
	Application* Application::Instance = nullptr;
	ImGuiLayer* Application::ImGuiLayerPtr = nullptr;

	Application::Application()
		: Camera(1.6f, -1.6f, .9f, -.9f)
	{
		Log::Get(LogTemp).Info(TEXT("{}"), __FUNCTION__);

		bRunning = true;
		Instance = this;
		WindowPtr = std::unique_ptr<Window>(Window::Create());
		WindowPtr->SetEventCallback(BIND_EVENT_ONE_PARAM(Application::OnEvent));
		ImGuiLayerPtr = MARS::CreateImGuiLayer();
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
			RenderCommands::SetClearColor(LinearColor::Gray);
			RenderCommands::Clear();

			Renderer::BeginScene(Camera);

			m_Shader2->Bind();
			m_Shader2->UploadUniformMat4(Camera.GetViewProjectionMatrix(), "ViewProjection");
			Renderer::Submit(SQ_VertArray);
			
			m_Shader->Bind();
			m_Shader2->UploadUniformMat4(Camera.GetViewProjectionMatrix(), "ViewProjection");
			Renderer::Submit(m_VertArray);
			
			Renderer::EndScene();

			ImGuiLayerPtr->OnBegin();
			UpdateLayers();
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
		UNUSED_PROPERTY(e)
		bRunning = false;
		return true;
	}

	void Application::UpdateLayers() const
	{
		for (auto* Element : m_LayerStack)
		{
			Element->OnUpdate();
			Element->RenderLayerUI();
		}
	}
}