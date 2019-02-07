#include "Windows_PlatformHandler.h"
#include "GLFW/glfw3.h"

using namespace MARS::PLATFORMWINDOWS;

WindowType _ActiveWindow = nullptr;

void RegisterWindow(WindowType InWindow)
{
	_ActiveWindow = InWindow;
}

WindowType GetRegisteredWindow()
{
	return _ActiveWindow;
}

bool ActiveWindow()
{
#if !PLATFORM_WINSTORE
	HWND _Forground = GetForegroundWindow();
	return _Forground == _ActiveWindow;
#else
	return true;
#endif
}