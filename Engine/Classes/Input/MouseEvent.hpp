#pragma once

#include "Core/Event.h"

namespace MARS
{
	class EXPORT_TYPE OnMouseMoved : public Event
	{
	public:
	
		OnMouseMoved(glm::vec2 MousePos)
		{
			this->MousePos = MousePos;
		}

		OnMouseMoved(float MouseX, float MouseY)
			: MousePos(MouseX, MouseY)
		{}

		FORCEINLINE glm::vec2 GetMousePos() const { return MousePos; }

		SET_CATEGORIES(CategoryMouse | CategoryInput)
		IMPLEMENT_INTERFACE_FUNCTIONS(MouseMoved)

	private:

		glm::vec2 MousePos;
	};

	class EXPORT_TYPE OnMouseScrolled : public Event
	{
	public:

		OnMouseScrolled(glm::vec2 Offset)
		{
			this->Offset = Offset;
		}

		OnMouseScrolled(float OffsetX, float OffsetY)
			: Offset(OffsetX, OffsetY)
		{}

		FORCEINLINE glm::vec2 GetOffset() const { return Offset; }

		SET_CATEGORIES(CategoryMouse | CategoryInput)
		IMPLEMENT_INTERFACE_FUNCTIONS(MouseScroll)

	private:

		glm::vec2 Offset;
	};

	class EXPORT_TYPE MouseInputEvent : public Event
	{
		
		int32 GetButtonID() const { return Button; }

	protected:

		MouseInputEvent(int32 Button)
		{
			this->Button = Button;
		}

	private:

		int32 Button;
	};

	class EXPORT_TYPE OnMouseButtonPressed : MouseInputEvent
	{
	public:

		OnMouseButtonPressed(int32 Button)
			: MouseInputEvent(Button)
		{}

		IMPLEMENT_INTERFACE_FUNCTIONS(MouseButtonPressed)
	};

	class EXPORT_TYPE OnMouseButtonReleased : public MouseInputEvent
	{
	public:

		OnMouseButtonReleased(int32 Button)
			: MouseInputEvent(Button)
		{}

		IMPLEMENT_INTERFACE_FUNCTIONS(MouseButtonReleased)
	};
}