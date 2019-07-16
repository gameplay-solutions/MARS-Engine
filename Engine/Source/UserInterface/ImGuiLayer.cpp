#include "UserInterface/ImGuiLayer.h"
#include "Rendering/OpenGL/ImGui_OpenGL_Renderer.h"
#include "Application/Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace MARS;

MARS::ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
{

}

MARS::ImGuiLayer::~ImGuiLayer()
{

}

void MARS::ImGuiLayer::OnUpdate()
{
	ImGuiIO& io = ImGui::GetIO();

	Application& App = Application::Get();
	io.DisplaySize = ImVec2(App.GetWindow().GetWidth(), App.GetWindow().GetHeight());

	float Delta = (float)glfwGetTime();
	io.DeltaTime = m_Time > 0.f ? (Delta - m_Time) : (1.f / 60.f);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

	static bool bShow = true;
	ImGui::ShowDemoWindow(&bShow);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void MARS::ImGuiLayer::OnAttach()
{
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGuiIO& io = ImGui::GetIO();
	io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
	io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

	// @TEMPHACK: Will use MARS custom keycodes eventually
	io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
	io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
	io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
	io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
	io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
	io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
	io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
	io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
	io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
	io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
	io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
	io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
	io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
	io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
	io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
	io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
	io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
	io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
	io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
	io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
	io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

	ImGui_ImplOpenGL3_Init("#version 410");
}

void MARS::ImGuiLayer::OnDetach()
{
}

void MARS::ImGuiLayer::OnEvent(Event& InEvent)
{
	EventDispatcher Dispatcher(InEvent);
	Dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_ONE_PARAM(ImGuiLayer::OnMouseButtonPressed));
	Dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_ONE_PARAM(ImGuiLayer::OnMouseButtonReleased));
	Dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_ONE_PARAM(ImGuiLayer::OnMouseMoved));
	Dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_ONE_PARAM(ImGuiLayer::OnMouseScrolled));
	Dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_ONE_PARAM(ImGuiLayer::OnKeyPressed));
	Dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_ONE_PARAM(ImGuiLayer::OnKeyReleased));
	Dispatcher.Dispatch<KeyTypedEvent>(BIND_EVENT_ONE_PARAM(ImGuiLayer::OnKeyTyped));
	Dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_ONE_PARAM(ImGuiLayer::OnWindowResized));
}

bool MARS::ImGuiLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseDown[e.GetMouseButton()] = true;

	return false;
}

bool MARS::ImGuiLayer::OnMouseButtonReleased(MouseButtonReleasedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseDown[e.GetMouseButton()] = false;

	return false;
}

bool MARS::ImGuiLayer::OnMouseMoved(MouseMovedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = ImVec2(e.GetX(), e.GetY());

	return false;
}

bool MARS::ImGuiLayer::OnMouseScrolled(MouseScrolledEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseWheel += e.GetYOffset();
	io.MouseWheelH += e.GetXOffset();

	return false;
}

bool MARS::ImGuiLayer::OnKeyPressed(KeyPressedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.KeysDown[e.GetKeyCode()] = true;

	io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
	io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
	io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
	io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

	return false;
}

bool MARS::ImGuiLayer::OnKeyReleased(KeyReleasedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.KeysDown[e.GetKeyCode()] = false;

	return false;
}

bool MARS::ImGuiLayer::OnKeyTyped(KeyTypedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	if (e.GetKeyCode() > 0 && e.GetKeyCode() < 0x10000)
	{
		io.AddInputCharacter((uint16)e.GetKeyCode());
	}

	return false;
}

bool MARS::ImGuiLayer::OnWindowResized(WindowResizeEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
	io.DisplayFramebufferScale = ImVec2(1.f, 1.f);
	glViewport(0, 0, e.GetWidth(), e.GetHeight());
	return false;
}