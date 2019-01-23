#pragma once

#include "Core/EngineCore.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <memory>

namespace MARS
{

	/** 
	 *	FMasterRenderContext is the entry point of the initializing the rendering system.
	 *	It all starts here
	 **/
	class FMasterRenderContext
	{
	
	public:
	
		void InitializeContexSytstem();
		void InitializeRenderSystem();
	
	protected:
	
		virtual void Init();
		
	private:
	
	};
	
	/** 
	 *	FWindowContext handles the creation and management of the GLFWwindow* context.
	 *	It also talks to the renderer so that the render knows when to change the frame buffer resolution
	 *	Primary loop is contained inside of this context as well
	 **/
	class FWindowContext : public FMasterRenderContext
	{
	
	public:
	
		FWindowContext();
	
	protected:

	private:
	
		virtual void Init() override;
		GLFWwindow* m_Window;

	};
}