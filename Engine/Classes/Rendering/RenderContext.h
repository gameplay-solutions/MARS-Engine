#pragma once

#include "CoreMinimal.h"

inline namespace MARS
{
	class RenderContext
	{
	public:

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
		virtual String GetAPIName() = 0;
		virtual String GetAPIFullName() = 0;

		virtual void Shutdown() = 0;
	};
}