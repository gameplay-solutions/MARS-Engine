#include "Core/EngineCore.h"

#ifdef PLATFORM_WINDOWS

extern MARS::Application* MARS::CreateApplication();

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