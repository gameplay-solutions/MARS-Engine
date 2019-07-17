#include "Windows_PlatformHandler.h"
#include "Core/Events/ApplicationEvent.h"
#include "Core/Events/MouseEvent.h"
#include "Core/Events/KeyEvent.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace MARS
{
	static bool s_bGLFWInit = false;

	Windows_PlatformHandler::Windows_PlatformHandler(const WindowProps& Props)
	{
		InitWindow(Props);
	}

	Windows_PlatformHandler::~Windows_PlatformHandler()
	{
		ShutdownWindow();
	}

	void Windows_PlatformHandler::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(Window);
	}

	uint32 Windows_PlatformHandler::GetWidth() const
	{
		return Data.Width;
	}

	uint32 Windows_PlatformHandler::GetHeight() const
	{
		return Data.Height;
	}

	void Windows_PlatformHandler::SetEventCallback(const EventCallback& CallbackFunction)
	{
		Data.EventCallbackFunction = CallbackFunction;
	}

	void Windows_PlatformHandler::SetVSync(bool bEnabled)
	{
		if (bEnabled) glfwSwapInterval(1); else glfwSwapInterval(0);
		Data.VSync = bEnabled;
	}

	bool Windows_PlatformHandler::IsUsingVSync() const
	{
		return Data.VSync;
	}

	Window* Window::Create(const WindowProps& Props)
	{
		return new Windows_PlatformHandler(Props);
	}

	void Windows_PlatformHandler::InitWindow(const WindowProps& Props)
	{
		Data.Title = Props.Title;
		Data.Width = Props.Width;
		Data.Height = Props.Height;

		Log::Get(LogGraphics).Info("Starting Window Construction. Platform: Windows");
		if (!s_bGLFWInit)
		{
			int32 SuccessCode = glfwInit();
			Assert(SuccessCode, "Could not Initialize GLFW")
			glfwSetErrorCallback([](int32 Error, const char* Desc){ Log::Get(LogError).Error("GLFW Error {0} : {1}", Error, Desc); });
			s_bGLFWInit = true;
		}

		Window = glfwCreateWindow((int)Props.Width, (int)Props.Height, Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(Window);
		int32 Status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		Assert(Status, "Failed to Init GLAD")
		glfwSetWindowUserPointer(Window, &Data);
		SetVSync(true);

		glfwSetWindowSizeCallback(Window, [](GLFWwindow* InWindow, int32 Width, int32 Height)
		{
			WindowData& _Data = *(WindowData*)glfwGetWindowUserPointer(InWindow);
			_Data.Width = Width;
			_Data.Height = Height;

			WindowResizeEvent _Event(Width, Height);
			_Data.EventCallbackFunction(_Event);
		});

		glfwSetWindowCloseCallback(Window, [](GLFWwindow* InWindow)
		{
			WindowData& _Data = *(WindowData*)glfwGetWindowUserPointer(InWindow);
			WindowCloseEvent _Event;
			_Data.EventCallbackFunction(_Event);
		});

		glfwSetKeyCallback(Window, [](GLFWwindow* InWindow, int32 Key, int32 Scancode, int32 Action, int32 Mods)
		{
			Scancode, Mods;
			WindowData& _Data = *(WindowData*)glfwGetWindowUserPointer(InWindow);
			switch (Action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent _Event(Key, 0);
					_Data.EventCallbackFunction(_Event);
					break;
				}

				case GLFW_RELEASE:
				{
					KeyReleasedEvent _Event(Key);
					_Data.EventCallbackFunction(_Event);
					break;
				}

				case GLFW_REPEAT:
				{
					KeyPressedEvent _Event(Key, 1);
					_Data.EventCallbackFunction(_Event);
					break;
				}
			}
		});

		glfwSetCharCallback(Window, [](GLFWwindow* InWindow, uint32 Char)
		{
			WindowData& _Data = *(WindowData*)glfwGetWindowUserPointer(InWindow);
			KeyTypedEvent _Event(Char);
			_Data.EventCallbackFunction(_Event);
		});

		glfwSetMouseButtonCallback(Window, [](GLFWwindow* InWindow, int32 Button, int32 Action, int32 Mods)
		{
			Mods;
			
			WindowData& _Data = *(WindowData*)glfwGetWindowUserPointer(InWindow);
			switch (Action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent _Event(Button);
					_Data.EventCallbackFunction(_Event);
					break;
				}

				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent _Event(Button);
					_Data.EventCallbackFunction(_Event);
					break;
				}
			}
		});

		glfwSetScrollCallback(Window, [](GLFWwindow * InWindow, double xOffset, double yOffset)
		{
			WindowData& _Data = *(WindowData*)glfwGetWindowUserPointer(InWindow);

			MouseScrolledEvent _Event((float)xOffset, (float)yOffset);
			_Data.EventCallbackFunction(_Event);
		});

		glfwSetCursorPosCallback(Window, [](GLFWwindow* InWindow, double xPos, double yPos)
		{
			WindowData& _Data = *(WindowData*)glfwGetWindowUserPointer(InWindow);

			MouseMovedEvent _Event((float)xPos, (float)yPos);
			_Data.EventCallbackFunction(_Event);
		});
	}

	void Windows_PlatformHandler::ShutdownWindow()
	{
		glfwDestroyWindow(Window);
	}
}