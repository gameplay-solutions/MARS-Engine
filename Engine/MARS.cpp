#include "Core/EngineCore.h"
#include "Rendering/GraphicsContext.h"
#include "Application/Application.h"

//MARS::FMasterRenderContext* RenderContex;
MARS::Application* App;

int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		/** @TODO(Chrisr): Handle command args */
		argv[argc];
	}

// 	Log::Write(LogInit, "Initializing MasterRenderContex");
// 
// 	RenderContex->InitializeContexSytstem();
// 	RenderContex->InitializeRenderSystem();
// 
// 	Log::Write(LogInit, "Initialized Render Contex. Rendering Engine is running.");

	App->Run();

	return 0;
}