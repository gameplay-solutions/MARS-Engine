#include "Core/EngineCore.h"

#if PLATFORM_WINDOWS

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

#endif // PLATFORM_WINDOWS