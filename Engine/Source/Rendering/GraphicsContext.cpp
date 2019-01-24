#include "Rendering/GraphicsContext.h"
#include "Rendering/Renderer.h"
#include <thread>

namespace MARS
{

	GLFWwindow* FWindows_PlatformContext::InitContext()
	{
		return nullptr;
	}

	#pragma warning(push)
	#pragma warning(disable:4100)
	void FramebufferSize_Callback(GLFWwindow* InWindow, int32 InWidth, int32 InHeight)
	{

	}
	#pragma warning(pop)
	
	void Update(GLFWwindow* InWindow)
	{
		while (!glfwWindowShouldClose(InWindow))
		{
			glfwPollEvents();
			glfwSwapBuffers(InWindow);
		}
	}

}