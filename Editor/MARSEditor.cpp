#include <MARSCore.h>
#include "imgui\imgui.h"
#include "UserInterface\ImGuiLayer.h"
#include "Rendering\BufferLayout.h"
#include "Rendering\VertexArray.h"
#include "Rendering\IndexBuffer.h"
#include "UserInterface\OutputLog.h"

class DetailsPanel : public ImGuiLayer
{

public:
	virtual void RenderLayerUI(bool* bRender) override
	{
		bool bTrue = true;
		bRender = &bTrue;

		ImGuiLayer::RenderLayerUI(bRender);

		// FPS Counter
		{
			const float Distance = 10.f;
			static int32 Corner = 0;
			ImGuiIO& Io = ImGui::GetIO();
			if (Corner != -1)
			{
				ImGuiViewport* _Viewport = ImGui::GetMainViewport();
				ImVec2 WindowPosition = ImVec2((Corner & 1) ? (_Viewport->Pos.x + _Viewport->Size.x - Distance) : (_Viewport->Pos.x + Distance), (Corner & 2) ? (_Viewport->Pos.y + _Viewport->Size.y - Distance) : (_Viewport->Pos.y +Distance));
				ImVec2 WindowPivotPosition = ImVec2((Corner & 1) ? 1.f : 0.f, (Corner & 2) ? 1.f : 0.f);
				ImGui::SetNextWindowPos(WindowPosition, ImGuiCond_Always, WindowPivotPosition);
				ImGui::SetNextWindowViewport(_Viewport->ID);
			}

			ImGui::SetNextWindowBgAlpha(0.15f);
			if (ImGui::Begin("Stats", bRender, (Corner != -1 ? ImGuiWindowFlags_NoMove : 0) | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav));
			{
				ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				ImGui::Separator();
				if (ImGui::IsMousePosValid())
				{
					ImGui::Text("Mouse X:(%.1f), Mouse Y:(%.1f)", Io.MousePos.x, Io.MousePos.y);
				}
				else
				{
					ImGui::Text("Mouse Position Invalid");
				}

				if (ImGui::BeginPopupContextWindow())
				{
					if (ImGui::MenuItem("Custom", nullptr, Corner == -1)) Corner = -1;
					if (ImGui::MenuItem("Top-left", nullptr, Corner == 0)) Corner = 0;
					if (ImGui::MenuItem("Top-right", nullptr, Corner == 1)) Corner = 1;
					if (ImGui::MenuItem("Bottom-left", nullptr, Corner == 2)) Corner = 2;
					if (ImGui::MenuItem("Bottom-right", nullptr, Corner == 3)) Corner = 3;
					if (bRender && ImGui::MenuItem("Close")) *bRender = false;
					ImGui::EndPopup();
				}
			}
			ImGui::End();
		}

		Draw(bRender);
	}

	static DetailsPanel* GetDetailsPanel()
	{
		static DetailsPanel* Instance = nullptr;
		if (Instance == nullptr)
		{
			Instance = new DetailsPanel;
		}

		return Instance;
	}

protected:

	void Draw(bool* bOpen)
	{
		Check(bOpen != nullptr)

		static bool bShowOutputLog = false;
		static bool bShowConsole = false;
		static bool bShowPropertyEditor = false;

		if (bShowOutputLog) 
		{
			_OutputLog = std::make_shared<OutputLog>("Output Log");
			_OutputLog->RenderLayerUI(&bShowOutputLog);
		}
		else
		{
			_OutputLog.reset();
		}

		ImGuiWindowFlags WindowFlags	=	0;
		static bool bNoClose			=	false;
		static bool bDisableDocking		=	false;
		static bool bDisableMenu		=	false;
		static bool bDisableTitlebar	=	false;

		if (bDisableDocking)	WindowFlags |= ImGuiWindowFlags_NoDocking;
		if (!bDisableMenu)		WindowFlags |= ImGuiWindowFlags_MenuBar;
		if (bDisableTitlebar)	WindowFlags |= ImGuiWindowFlags_NoTitleBar;
		if (bNoClose)			bOpen		 = nullptr;

		ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

		if (!ImGui::Begin(GetName().c_str(), bOpen, WindowFlags))
		{
			ImGui::End();
			return;
		}

		ImGui::PushItemWidth(ImGui::GetFontSize() * -12); // fixed width for text/labels

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Menu"))
			{
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Windows"))
			{
				ImGui::MenuItem("Output Log", nullptr, &bShowOutputLog);
				ImGui::MenuItem("Property Editor", nullptr, &bShowPropertyEditor);
				ImGui::MenuItem("Console", nullptr, &bShowConsole);
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Tools"))
			{
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Text("MARS Engine Version (%f)", MARS_VERSION);
		ImGui::Spacing();

		if (ImGui::CollapsingHeader("World Settings"))
		{
			ImGui::Text("Edit Default World Settings");
		}

		if (ImGui::CollapsingHeader("Window Settings"))
		{
			ImGuiIO& IO = ImGui::GetIO();
			ImGui::CheckboxFlags("Enable Docking", (uint32*)IO.ConfigFlags, ImGuiConfigFlags_DockingEnable);
		}

		ImGui::End();
	}

private:

	DetailsPanel()
		: ImGuiLayer("Details Panel")
	{
		bShowDemoWindow = false;
	}
	~DetailsPanel() { }
	std::shared_ptr<OutputLog> _OutputLog;
};

class DelegateTest
{
public:

	void VoidFunc()
	{
		Log::Get(LogTemp).Info("{0}", __FUNCTION__);
	}

	int32 Int32Func()
	{
		Log::Get(LogTemp).Info("{0}", __FUNCTION__);
		return 40;
	}

	void VoidWithParamFunc(int32 a, int32 b)
	{
		Log::Get(LogTemp).Info("{0}, {1}, {2}, {3}", a, b, __FUNCTION__, __FUNCSIG__);
	}

	int32 Int32WithParamFunc(float a)
	{
		Log::Get(LogTemp).Info("{0}, {1}, {2}", a, __FUNCTION__, __FUNCSIG__);
		return 70;
	}
};

class MARSEditor : public MARS::Application
{
public:
	MARSEditor()
	{
		Log::Get(LogTemp).Info(TEXT("{}"), __FUNCTION__);
		
		PushOverlay(GetImGuiLayer());
		GetImGuiLayer()->bDrawUserInterface = true;

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
			 0.5f, -0.5f, 0.f,
			 0.5f,	0.5f, 0.f,
			-0.5f,	0.5f, 0.f
		};

		SQ_VertBuffer.reset(VertexBuffer::Create(SQ_verts, sizeof(SQ_verts)));

		SQ_VertBuffer->SetLayout({ { ShaderDataType::Float3, "a_Position" } });

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

		DelegateTest l;
		auto VoidDelegate = DECLARE_DELEGATE(DelegateTest, VoidFunc, l);
		auto Int32Delegate = DECLARE_DELEGATE(DelegateTest, Int32Func, l);
		auto VoidWithParamsDelegate = DECLARE_DELEGATE_PARAMS(DelegateTest, VoidWithParamFunc, l);
		auto Int32WithParamsDelegate = DECLARE_DELEGATE_PARAMS(DelegateTest, Int32WithParamFunc, l);
		
		VoidDelegate();
		Log::Get(LogTemp).Info("Int32Delegate returned {}", Int32Delegate());
		VoidWithParamsDelegate(15, 5);
		Int32WithParamsDelegate(8);
	}



	~MARSEditor()
	{
		
	}
};

MARS::Application* MARS::CreateApplication()
{
	return new MARSEditor();
}

MARS::ImGuiLayer* MARS::CreateImGuiLayer()
{
	return DetailsPanel::GetDetailsPanel();
}