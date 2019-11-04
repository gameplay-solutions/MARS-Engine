#include "Rendering/OpenGL/OpenGLContext.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

MARS::OpenGLContext::OpenGLContext(GLFWwindow* WindowHandle)
	: m_WindowHandle(WindowHandle)
{
	Assertf(m_WindowHandle, "WindowHandle is nullptr")
}

void MARS::OpenGLContext::Init()
{
	glfwMakeContextCurrent(m_WindowHandle);
	int32 Status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	Assertf(Status, "Failed to Init GLAD")

	String _Version = (char*)glGetString(GL_VERSION);
	APIName = "OpenGL " + _Version;

	Log::Get(LogInit).Info("OpenGL Context Created.");
	Log::Get(LogInit).Warning(" Hardware Vender:	{}", glGetString(GL_VENDOR));
	Log::Get(LogInit).Warning(" Hardware Model:	{}", glGetString(GL_RENDERER));
	Log::Get(LogInit).Warning(" OpenGL Version:	{}", glGetString(GL_VERSION));
}

void MARS::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}

String MARS::OpenGLContext::GetAPIFullName()
{
	return APIName;
}

String MARS::OpenGLContext::GetAPIName()
{
	return "OpenGL";
}

void MARS::OpenGLContext::Shutdown()
{
	
}
