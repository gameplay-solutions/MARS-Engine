#pragma once

#include "Event.h"

/*
 *	@TODO(Chrisr): Update getter implementation when custom vector class has been written to return something like:
 *	inline Vector2D GetOffset() const { return Offset; }
 *	
 *	Offset.x && Mouse.y
 **/

namespace MARS
{
	class EXPORT_TYPE MouseMovedEvent : public Event
	{
	public:

		MouseMovedEvent(float x, float y) : MouseX(x), MouseY(y) {}

		inline float GetX() const { return MouseX; }
		inline float GetY() const { return MouseY; }


		EVENT_CLASS_CATEGORY(CategoryMouse | CategoryInput)
		EVENT_CLASS_TYPE(MouseMoved)

	private:

		float MouseX, MouseY;
	};

	class EXPORT_TYPE MouseScrolledEvent : public Event
	{
	public:

		MouseScrolledEvent(float x, float y) : OffsetX(x), OffsetY(y) {}

		inline float GetXOffset() const { return OffsetX; }
		inline float GetYOffset() const { return OffsetY; }

		EVENT_CLASS_TYPE(MouseScroll)
		EVENT_CLASS_CATEGORY(CategoryMouse | CategoryInput)

	private:

		float OffsetX, OffsetY;
	};

	class EXPORT_TYPE MouseButtonEvent : public Event
	{
	public:
		
		inline int32 GetMouseButton() const { return Button; }

		EVENT_CLASS_CATEGORY(CategoryMouse | CategoryInput)

	protected:

		MouseButtonEvent(int32 InButton) : Button(InButton) { }

		int32 Button;
	};

	class EXPORT_TYPE MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:

		MouseButtonPressedEvent(int32 InButton) : MouseButtonEvent(InButton) { }

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class EXPORT_TYPE MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:

		MouseButtonReleasedEvent(int32 InButton) : MouseButtonEvent(InButton) { }

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}