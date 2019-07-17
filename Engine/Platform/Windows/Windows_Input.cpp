#include "Windows_Input.h"

#include <GLFW/glfw3.h>
#include "Application/Application.h"

MARS::Input* MARS::Input::Instance = new WindowsInput();

bool MARS::WindowsInput::IsKeyPressed_Implementation(int32 Key)
{
	auto _Window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	auto _State = glfwGetKey(_Window, Key);
	return _State == GLFW_PRESS || _State == GLFW_REPEAT;

}

bool MARS::WindowsInput::IsMouseButtonPressed_Implementation(int32 Button)
{
	auto _Window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	auto _State = glfwGetMouseButton(_Window, Button);
	return _State == GLFW_PRESS;
}

float MARS::WindowsInput::GetMouseX_Implementation()
{
	auto[x, y] = GetMousePos_Implementation();
	return x;
}

float MARS::WindowsInput::GetMouseY_Implementation()
{
	auto[x, y] = GetMousePos_Implementation();
	return y;
}

std::pair<float, float> MARS::WindowsInput::GetMousePos_Implementation()
{
	auto _Window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	double xPos, yPos;
	glfwGetCursorPos(_Window, &xPos, &yPos);

	return { xPos, yPos };
}
