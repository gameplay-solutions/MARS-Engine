#include "Rendering/GraphicsContext.h"
#include "Rendering/Renderer.h"
#include <thread>

namespace MARS
{

<<<<<<< HEAD
	GLFWwindow* FWindows_PlatformContext::InitContext()
	{
		return nullptr;
=======
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
>>>>>>> 937241bc59ca51c55a7a4b49751867cccba3322a
	}

}