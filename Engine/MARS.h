#include "Core/EngineCore.h"

#ifdef PLATFORM_WINDOWS

MARS::Application* MARS::CreateApplication();

int32 main(int32 argc, char* argv[])
{
	if (argc > 1)
	{
		/** @TODO(Chrisr): Handle command args */
		argv[argc];
	}

	auto* App = MARS::CreateApplication();
	App->InitMARS();
	delete App;

	return 0;
}

#else
#error Unsupported platform, MARS unable to compile!
#endif // PLATFORMS