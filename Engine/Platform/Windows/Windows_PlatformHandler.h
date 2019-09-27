#pragma once

#include "Application/Window.h"
#include "Rendering/RenderContext.h"

struct GLFWwindow;

namespace MARS
{
	/** 
	 *	Handle Microsoft Windows platform specific operations here
	 **/
	class Windows_PlatformHandler : public Window
	{
	public:

		Windows_PlatformHandler(const WindowProps& Props);
		virtual ~Windows_PlatformHandler();

		void Refresh() override;
		virtual uint32 GetWidth() const override;
		virtual uint32 GetHeight() const override;
		virtual void SetEventCallback(const EventCallback& CallbackFunction) override;
		virtual void SetVSync(bool bEnabled) override;
		virtual bool IsUsingVSync() const override;
		virtual void* GetNativeWindow() const override;

	private:

		void InitWindow(const WindowProps& Props);
		void ShutdownWindow();

		GLFWwindow* m_Window;
		RenderContext* m_Context;

		struct WindowData
		{
			String Title;
			uint32 Width, Height;
			bool VSync;
			EventCallback EventCallbackFunction;
		} Data;
	};
}