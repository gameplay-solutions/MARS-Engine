#pragma once

#include "Core/EngineCore.h"
#include <functional>

namespace MARS
{
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
		ApplicationTick,
		ApplicationUpdate,
		ApplicationRender,
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

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const {}
		virtual int32 GetCategoryFlag() const {}
		
		FORCEINLINE bool IsInCategory(EventCategory Cat)
		{
			return GetCategoryFlag() & Cat;
		}

	private:

		bool bEventHandled = false;
	};
	
	class FEventDispatcher
	{
		template<typename T>
		using EventFunction = std::function<bool(T&)>;
	};
}