#pragma once

#include "CoreMinimal.h"
#include "Input/InputHandler.h"

inline namespace MARS
{
	class WindowsInput : public Input
	{

	protected:

		virtual bool IsKeyPressed_Implementation(int32 Key) override;
		virtual bool IsMouseButtonPressed_Implementation(int32 Button) override;
		virtual std::pair<double, double> GetMousePos_Implementation() override;
		virtual float GetMouseX_Implementation() override;
		virtual float GetMouseY_Implementation() override;
	};
}