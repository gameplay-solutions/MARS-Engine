#pragma once

#include "Core/EngineCore.h"

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
		CategoryApplication		= 1 << 0,
		CategoryInput			= 1 << 1,
		CategoryKeyboard		= 1 << 2,
		CategoryMouse			= 1 << 3,
		CategoryMouseButton		= 1 << 4,
	};

	#define EVENT_CLASS_TYPE(x) static EventType GetStaticType() { return EventType::##x; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #x; }

	#define EVENT_CLASS_CATEGORY(x) virtual int32 GetCategoryFlags() const override { return x; }

	class EXPORT_TYPE Event
	{
		friend class EventDispatcher;

	public:
		
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int32 GetCategoryFlags() const = 0;
		virtual String ToString() const { return GetName(); }

		__forceinline bool IsEventHandled() const { return bEventHandled; }

		inline bool IsInCategory(EventCategory InCategory)
		{
			return GetCategoryFlags() & InCategory;
		}

	protected:

		bool bEventHandled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using CallbackFunction = std::function<bool(T&)>;

	public:

		EventDispatcher(Event& e) : AwaitingEvent(e) {}

		template<typename T>
		bool Dispatch(CallbackFunction<T> Func)
		{
			if (AwaitingEvent.GetEventType() == T::GetStaticType())
			{
				AwaitingEvent.bEventHandled = Func(*(T*)&AwaitingEvent);
				return true;
			}
			return false;
		}

	private:

		Event& AwaitingEvent;
	};

	inline std::ostream& operator << (std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}