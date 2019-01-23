#include "Application/Application.h"
#include "Rendering/GraphicsContext.h"

MARS::FMasterRenderContext* RenderContex;

namespace MARS
{
	Application::Application()
	{
	
	}
	
	void Application::Run()
	{
		RenderContex->InitializeContexSytstem();
	}
}

