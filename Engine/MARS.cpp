#include "Core/EngineCore.h"
#include "Application/Application.h"
#include "GLFW/glfw3.h"

int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		/** @TODO(Chrisr): Handle command args */
		argv[argc];
	}
	
	MARS::Application::Get().StartEngine();

	return 0;
}