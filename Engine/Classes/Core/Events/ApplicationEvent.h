#pragma once

#include "Event.h"

namespace MARS
{
	class EXPORT_TYPE WindowResizeEvent : public Event
	{
	public:

		WindowResizeEvent(uint32 InWidth, uint32 InHeight) : Width(InWidth), Height(InHeight) { }

		inline uint32 GetWidth() const { return Width; }
		inline uint32 GetHeight() const { return Height; }

		EVENT_CLASS_CATEGORY(CategoryApplication)
			EVENT_CLASS_TYPE(WindowResize)

	private:

		uint32 Width, Height;
	};

	class EXPORT_TYPE WindowCloseEvent : public Event
	{
	public:
		
		WindowCloseEvent() {}

		EVENT_CLASS_CATEGORY(CategoryApplication)
		EVENT_CLASS_TYPE(WindowClose)
	};
}