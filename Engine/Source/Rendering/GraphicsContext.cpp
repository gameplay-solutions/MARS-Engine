#include "Rendering/GraphicsContext.h"
#include "Rendering/Renderer.h"
#include <thread>

namespace MARS
{
	/** Start Callbacks */

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

	/** End Callbacks */

	void FMasterRenderContext::InitializeContexSytstem()
	{
		std::unique_ptr<FWindowContext> WindowContext(new FWindowContext());
	}
	
	void FMasterRenderContext::InitializeRenderSystem()
	{
		Init();
	}

	void FMasterRenderContext::Init()
	{
		
	}

	FWindowContext::FWindowContext()
	{
		Init();
	}

	void FWindowContext::Init()
	{
		Log::Write(LogGraphics, "Creation of window started");
	
		if (glfwInit())
		{
			Log::Write(LogGraphics, "GLFW has started initialization");
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
			glfwWindowHint(GLFW_RESIZABLE, true);
			glfwWindowHint(GLFW_MAXIMIZED, true);

			GLFWwindow* _WindowPtr = glfwCreateWindow(1920, 1080, "MARS", nullptr, nullptr);
			if (!_WindowPtr)
			{
				glfwTerminate();
			}

			glfwMakeContextCurrent(_WindowPtr);
			glfwSetInputMode(_WindowPtr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

			/** Register Callbacks */
			glfwSetFramebufferSizeCallback(_WindowPtr, FramebufferSize_Callback);
			/** End Register Callbacks */

			int32 _Width, _Height;
			glfwGetFramebufferSize(_WindowPtr, &_Width, &_Height);
			Log::Write(LogGraphics, "GLFW has been initialized");

			Log::Write(LogGraphics, "Starting Render Loop");
			Update(_WindowPtr);
		}
	}
}