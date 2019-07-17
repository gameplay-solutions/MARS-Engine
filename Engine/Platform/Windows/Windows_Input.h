#pragma once

#include "Core/EngineCore.h"
#include "Input/InputHandler.h"

namespace MARS
{
	class WindowsInput : public Input
	{

	protected:

		virtual bool IsKeyPressed_Implementation(int32 Key) override;
		virtual bool IsMouseButtonPressed_Implementation(int32 Button) override;
		virtual std::pair<float, float> GetMousePos_Implementation() override;
		virtual float GetMouseX_Implementation() override;
		virtual float GetMouseY_Implementation() override;
	};
}