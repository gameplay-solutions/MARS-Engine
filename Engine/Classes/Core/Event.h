#pragma once

#include "Core/EngineCore.h"
#include <functional>

namespace MARS
{
	/** @todo(Chrisr): Maybe have this be stored in an .ini and setup by MHT? */
	enum class EventType
	{
		None = 0,
		WindowClose,
		WindowResize,
		WindowFocus,
		WindowLostFocus,
		WindowMoved,
		KeyPressed,
		KeyReleased,
		KeyTyped,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScroll,
	};

	enum EventCategory
	{
		None = 0,
		CategoryApplication = 1 << 0,
		CategoryInput = 1 << 1,
	};

	class FEvent
	{
	public:
	private:

	};
}