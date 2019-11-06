#include "UserInterface/ImGuiLayer.h"
#include "imgui/imgui.h"

#include "imgui/examples/imgui_impl_glfw.h"
#include "imgui/examples/imgui_impl_opengl3.h"

#include "Application/Application.h"

#include <GLFW/glfw3.h>

ImGuiLayer::ImGuiLayer(const String& InWindowName) : Layer(InWindowName) { Log::Get(LogGraphics).Info("ImGuiLayer Constructed"); }
ImGuiLayer::~ImGuiLayer() { Log::Get(LogGraphics).Info("ImGuiLayer Destroyed"); }

bool MARS::ImGuiLayer::bShowDemoWindow = true;

void MARS::ImGuiLayer::OnAttach()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui::StyleColorsDark();

	ImGuiStyle& Style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		Style.WindowRounding = 0.0f;
		Style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	Application& App = Application::Get();
	GLFWwindow* Window = static_cast<GLFWwindow*>(App.GetWindow().GetNativeWindow());

	ImGui_ImplGlfw_InitForOpenGL(Window, true);
	ImGui_ImplOpenGL3_Init();
}

void MARS::ImGuiLayer::OnDetach()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void MARS::ImGuiLayer::OnBegin()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void MARS::ImGuiLayer::RenderLayerUI(bool* bRender)
{
	//ImGui::ShowDemoWindow(bRender);
}

void MARS::ImGuiLayer::OnEnd()
{
	ImGuiIO& io = ImGui::GetIO();
	Application& app = Application::Get();
	io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* BackupContext = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(BackupContext);
	}
}