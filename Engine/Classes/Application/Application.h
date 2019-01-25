#pragma once

#include "Core/EngineCore.h"

namespace MARS
{
	class __declspec(dllexport) Application
	{
	public:

		Application();
		virtual ~Application();

		/** 
		 *	Global init function. Called by the application.
		 *	Starts the main loop and creates the Window class.
		 *	This is the first init function call of the engine
		 *	so it's a bad idea to try and add code here, 
		 *	it will most likely rely on system that haven't been initialized yet.
		 **/
		void InitMARS();
	};

	Application* CreateApplication();
}