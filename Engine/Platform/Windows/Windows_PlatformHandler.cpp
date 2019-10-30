#include "Windows_PlatformHandler.h"
#include "Core/Events/ApplicationEvent.h"
#include "Core/Events/MouseEvent.h"
#include "Core/Events/KeyEvent.h"
#include "Rendering/OpenGL/OpenGLContext.h"
#include "GLFW/glfw3.h"

static bool s_bGLFWInit = false;

namespace MARS
{

	Windows_PlatformHandler::Windows_PlatformHandler(const WindowProps& Props)
	{
		InitWindow(Props);
	}

	Windows_PlatformHandler::~Windows_PlatformHandler()
	{
		ShutdownWindow();
	}

	void Windows_PlatformHandler::Refresh()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
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


	void* Windows_PlatformHandler::GetNativeWindow() const
	{
		return m_Window;
	}

	void Windows_PlatformHandler::InitWindow(const WindowProps& Props)
	{
		Data.Title = Props.Title;
		Data.Width = Props.Width;
		Data.Height = Props.Height;

		Log::Get(LogInit).Info("Constructing a {0}-{1} Window using {2}", Data.Width, Data.Height, "OpenGL 4.3");
		if (!s_bGLFWInit)
		{
			int32 SuccessCode = glfwInit();
			Assert(SuccessCode, "Could not Initialize GLFW")
			glfwSetErrorCallback([](int32 Error, const char* Desc){ Log::Get(LogError).Error("GLFW Error {0} : {1}", Error, Desc); });
			s_bGLFWInit = true;
		}

		m_Window = glfwCreateWindow((int)Props.Width, (int)Props.Height, Data.Title.c_str(), nullptr, nullptr);
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		Log::Get(LogInit).Info("{} constructed. Running Platform Init", Data.Title);
		glfwSetWindowUserPointer(m_Window, &Data);
		SetVSync(true);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* InWindow, int32 Width, int32 Height)
		{
			WindowData& _Data = *(WindowData*)glfwGetWindowUserPointer(InWindow);
			_Data.Width = Width;
			_Data.Height = Height;

			WindowResizeEvent _Event(Width, Height);
			_Data.EventCallbackFunction(_Event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* InWindow)
		{
			WindowData& _Data = *(WindowData*)glfwGetWindowUserPointer(InWindow);
			WindowCloseEvent _Event;
			_Data.EventCallbackFunction(_Event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* InWindow, int32 Key, int32 Scancode, int32 Action, int32 Mods)
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

		glfwSetCharCallback(m_Window, [](GLFWwindow* InWindow, uint32 Char)
		{
			WindowData& _Data = *(WindowData*)glfwGetWindowUserPointer(InWindow);
			KeyTypedEvent _Event(Char);
			_Data.EventCallbackFunction(_Event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* InWindow, int32 Button, int32 Action, int32 Mods)
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

		glfwSetScrollCallback(m_Window, [](GLFWwindow * InWindow, double xOffset, double yOffset)
		{
			WindowData& _Data = *(WindowData*)glfwGetWindowUserPointer(InWindow);

			MouseScrolledEvent _Event((float)xOffset, (float)yOffset);
			_Data.EventCallbackFunction(_Event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* InWindow, double xPos, double yPos)
		{
			WindowData& _Data = *(WindowData*)glfwGetWindowUserPointer(InWindow);

			MouseMovedEvent _Event((float)xPos, (float)yPos);
			_Data.EventCallbackFunction(_Event);
		});

		Log::Get(LogInit).Info("Windows Platform Init Complete");
	}

	void Windows_PlatformHandler::ShutdownWindow()
	{
		m_Context->Shutdown();
		delete m_Context;
		glfwDestroyWindow(m_Window);
	}

	Window* Window::Create(const WindowProps& Props)
	{
		return new Windows_PlatformHandler(Props);
	}
}