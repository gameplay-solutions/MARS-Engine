#include "Core/EngineCore.h"

#if PLATFORM_WINDOWS

MARS::Application* MARS::CreateApplication();

int main(int argc, char* argv[])
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