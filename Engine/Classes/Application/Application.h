#pragma once

#include "Core/EngineCore.h"
#include "glad/glad.h"

namespace MARS
{
	class FEvent;
	struct GLFWwindow;
	class FRenderer;

	class Application
	{
	public:

		virtual void StartEngine();
		void Clean();
		void NewFrame();
		void RenderDebugGUI();

		static Application& Get();

	protected:

		virtual void InitSystems(GLFWwindow* Window, GLADloadproc LoadProc);

	private:

		Application();
		static Application* m_App;

	};
}