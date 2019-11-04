#include "Application/Application.h"
#include "Input/InputHandler.h"
#include "UserInterface/ImGuiLayer.h"
#include "Rendering/BufferLayout.h"
#include "Rendering/Renderer.h"
#include "UserInterface/OutputLog.h"
#include "Rendering/RenderTypes.h"

inline namespace MARS
{
	Application* Application::Instance = nullptr;
	OutputLog Application::GlobalOutputLog = OutputLog();

	Application::Application()
		: Camera(-1.6f, 1.6f, -.9f, .9f)
	{
		bRunning = true;
		Instance = this;
		WindowPtr = std::unique_ptr<Window>(Window::Create());
		WindowPtr->SetEventCallback(BIND_EVENT_ONE_PARAM(Application::OnEvent));

		ImGuiLayerPtr = new ImGuiLayer;
		PushOverlay(ImGuiLayerPtr);

		m_VertArray.reset(VertexArray::Create());

		float verts[3 * 7] =
		{
			-0.5f, -0.5f, 0.f, 0.2f, 0.8f, 0.2f, 1.f,
			0.5f, -0.5f, 0.0f, 0.8f, 0.3f, 0.8f, 1.f,
			0.f, 0.5f, 0.f, 0.4f, 0.7f, 0.2f, 1.f
		};

		m_VertBuffer.reset(VertexBuffer::Create(verts, sizeof(verts)));
		BufferLayout Layout =
		{
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		};

		m_VertBuffer->SetLayout(Layout);
		m_VertArray->AddVertexBuffer(m_VertBuffer);

		uint32 indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32)));
		m_VertArray->SetIndexBuffer(m_IndexBuffer);

		SQ_VertArray.reset(VertexArray::Create());
		float SQ_verts[3 * 4] =
		{
			-0.5f, -0.5f, 0.f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.f,
			-0.5f, 0.5f, 0.f
		};

		SQ_VertBuffer.reset(VertexBuffer::Create(SQ_verts, sizeof(SQ_verts)));

		SQ_VertBuffer->SetLayout({{ ShaderDataType::Float3, "a_Position" }});

		SQ_VertArray->AddVertexBuffer(SQ_VertBuffer);

		uint32 SQ_indices[6] = { 0, 1, 2, 2, 3, 0 };
		SQ_IndexBuffer.reset(IndexBuffer::Create(SQ_indices, sizeof(SQ_indices) / sizeof(uint32)));
		SQ_VertArray->SetIndexBuffer(SQ_IndexBuffer);

		String vSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			uniform mat4 ViewProjection;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		String fSource = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		String vSource2 = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;
			out vec4 v_Color;

			uniform mat4 ViewProjection;

			void main()
			{
				v_Position = a_Position;
				gl_Position = ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		String fSource2 = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_Shader = std::make_shared<Shader>(vSource, fSource);
		m_Shader2 = std::make_shared<Shader>(vSource2, fSource2);
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
		UNUSED_PROPERTY(e)
		bRunning = false;
		return true;
	}
}