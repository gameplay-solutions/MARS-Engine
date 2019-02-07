#pragma once

#include "Core/EngineCore.h"

namespace MARS
{
	inline namespace PLATFORMWINDOWS
	{
#ifndef PLATFORM_WINSTORE
		using WindowType = HWND;
#else
		typedef Windows::UI::Core::CoreWindow^ WindowType;
#endif

	
	void RegisterWindow(WindowType InWindow);
	WindowType GetRegisteredWindow();
	bool ActiveWindow();
	}
}