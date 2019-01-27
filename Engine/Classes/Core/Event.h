#pragma once

#include "Core/EngineCore.h"

namespace MARS
{

#define SET_CATEGORIES(x)	virtual int32 GetFlags() const override { return x; }

#define IMPLEMENT_INTERFACE_FUNCTIONS(x)										\
static EventType GetStaticType() { return EventType::##x; }						\
virtual EventType GetEventType() const override { return GetStaticType(); }		\
virtual const char* GetName() const override { return #x; }


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
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScroll,
	};

	enum EventCategory
	{
		None = 0,
		CategoryApplication = 1 << 0,
		CategoryInput		= 1 << 1,
		CategoryMouse		= 1 << 2,
		CategoryKeyboard	= 1 << 3,
	};


	class __declspec(dllexport) Event
	{
	public:

		/** 
		 *	@Return: returns the EventType this event is responding to 
		 **/
		virtual EventType GetEventType() const = 0;

		/** @note(Chrisr): Maybe make this Debug only? */
		/** 
		 *	@Return: returns the current name of the event 
		 **/
		virtual const char* GetName() const = 0;

		/** 
		 *	@Return: returns a bitfield of the category flags this event has set
		 * 
		 **/
		virtual int32 GetFlags() const = 0;

		/** 
		 *	@Param Flag: The flag that will be checked
		 *	@Return: Checks whether this event has the flag set.
		 **/
		FORCEINLINE bool HasFlag(EventCategory Flag)
		{
			return GetFlags() & Flag;
		}

		bool Handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventCallback = std::function<bool(T&)>;

	public:

		EventDispatcher(Event& EventToDispatch)
			: Payload(EventToDispatch)
		{}

		template<typename T>
		bool Dispatch(EventCallback<T> Callback)
		{
			if (Payload.GetEventType() == T::GetStaticType())
			{
				Payload.Handled = Callback(*(T*)&Payload);
			}

			return Payload.Handled;
		}

	private:

		Event& Payload;
	};
}