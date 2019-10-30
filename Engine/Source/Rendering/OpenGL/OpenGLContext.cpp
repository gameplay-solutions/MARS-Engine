#include "Rendering/OpenGL/OpenGLContext.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

MARS::OpenGLContext::OpenGLContext(GLFWwindow* WindowHandle)
	: m_WindowHandle(WindowHandle)
{
	Assert(m_WindowHandle, "WindowHandle is nullptr")
}

void MARS::OpenGLContext::Init()
{
	glfwMakeContextCurrent(m_WindowHandle);
	int32 Status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	Assert(Status, "Failed to Init GLAD")
}

void MARS::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}

String MARS::OpenGLContext::GetAPIFullName()
{
	return "OpenGL v4.3";
}

String MARS::OpenGLContext::GetAPIName()
{
	return "OpenGL";
}

void MARS::OpenGLContext::Shutdown()
{
	
}
