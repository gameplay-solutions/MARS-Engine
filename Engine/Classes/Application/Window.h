#pragma once

#include "Core/EngineCore.h"

namespace MARS
{
	struct WindowProps
	{
		String Title;
		uint32 Width, Height;

		WindowProps(const String& InTitle = "MARS Engine", uint32 InWidth = 1280, uint32 InHeight = 720)
		: Title(InTitle)
		, Width(InWidth)
		, Height(InHeight)
		{}
	};

	class EXPORT_TYPE Window
	{
	public:

		using EventCallback = std::function<void(Event&)>;

		virtual void Refresh() = 0;

		virtual uint32 GetWidth() const = 0;
		virtual uint32 GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallback& CallbackFunction) = 0;
		virtual void SetVSync(bool bEnabled) = 0;
		virtual bool IsUsingVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& WindowProperties = WindowProps());
	};
}