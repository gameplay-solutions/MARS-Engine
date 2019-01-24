#pragma once

#include "Core/EngineCore.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <memory>

namespace MARS
{
	struct FPlatform_WindowContext
	{
		virtual GLFWwindow* InitContext() {}
	};

	struct FWindows_PlatformContext : public FPlatform_WindowContext
	{
		virtual GLFWwindow* InitContext() override;
	};
}