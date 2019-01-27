#pragma once

#include "Core/Event.h"

namespace MARS
{
	class __declspec(dllexport) KeyInputEvent : public Event
	{
	public:
		
		FORCEINLINE int32 GetKeyCode() const { return KeyCode; }

		SET_CATEGORIES(CategoryKeyboard | CategoryInput)

	protected:

		KeyInputEvent(int32 Key)
			: KeyCode(Key)
		{}

	private:

		int32 KeyCode;
	};

	class __declspec(dllexport) OnKeyPressed : public KeyInputEvent
	{
	public:
		
		OnKeyPressed(int32 Key, bool Repeating)
			: KeyInputEvent(Key)
			, RepeatKey(Repeating)
		{}

		FORCEINLINE int32 GetRepeating() const { return RepeatKey; }

		IMPLEMENT_INTERFACE_FUNCTIONS(KeyPressed)

	private:
		
		bool RepeatKey;
	};

	class __declspec(dllexport) OnKeyReleased : public KeyInputEvent
	{
	public:

		OnKeyReleased(int32 Key)
			: KeyInputEvent(Key)
		{}

		IMPLEMENT_INTERFACE_FUNCTIONS(KeyReleased)
	};
}