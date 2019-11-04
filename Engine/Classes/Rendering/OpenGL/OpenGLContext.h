#pragma once

#include "Rendering/RenderContext.h"

struct GLFWwindow;

inline namespace MARS
{
	class OpenGLContext : public RenderContext
	{
	public:

		OpenGLContext(GLFWwindow* WindowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
		virtual String GetAPIFullName() override;
		virtual String GetAPIName() override;
		virtual void Shutdown() override;

	private:

		GLFWwindow* m_WindowHandle;
		String APIName;
	};
}