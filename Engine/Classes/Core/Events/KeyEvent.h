#pragma once

#include "Event.h"

namespace MARS
{
	class EXPORT_TYPE KeyEvent : public Event
	{
	public:
		
		inline int32 GetKeyCode() const { return KeyCode; }

		EVENT_CLASS_CATEGORY(CategoryKeyboard | CategoryInput)

	protected:

		KeyEvent(int32 InKeyCode) 
			: KeyCode(InKeyCode) { }

		int32 KeyCode;
	};

	class EXPORT_TYPE KeyPressedEvent : public KeyEvent
	{
	public:

		KeyPressedEvent(int32 InKeyCode, int32 InRepeatCount) : KeyEvent(InKeyCode), RepeatCount(InRepeatCount) {}

		inline int32 GetRepeatCount() const { return RepeatCount; }

		String ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << KeyCode << " (" << RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:

		int32 RepeatCount;

	};

	class EXPORT_TYPE KeyReleasedEvent : public KeyEvent
	{
	public:

		KeyReleasedEvent(int32 InKeyCode) : KeyEvent(InKeyCode) { }

		String ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent " << KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class EXPORT_TYPE KeyTypedEvent : public KeyEvent
	{
	public:

		KeyTypedEvent(int32 KeyCode) : KeyEvent(KeyCode) {}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}