#pragma once

#include "Types\CoreTypes.h"
#include <utility>

namespace MARS
{
	class EXPORT_TYPE Input
	{
	public:
		
		inline static bool IsKeyPressed(int32 Key) { return Instance->IsKeyPressed_Implementation(Key); }
		inline static bool IsMouseButtonPressed(int32 Button) { return Instance->IsMouseButtonPressed_Implementation(Button); }
		inline static std::pair<float, float> GetMousePos() { return Instance->GetMousePos_Implementation(); }
		inline static float GetMouseX() { return Instance->GetMouseX_Implementation(); }
		inline static float GetMouseY() { return Instance->GetMouseX_Implementation(); }

	protected:

		virtual bool IsMouseButtonPressed_Implementation(int32 Button) = 0;
		virtual bool IsKeyPressed_Implementation(int32 Key) = 0;
		virtual std::pair<float, float> GetMousePos_Implementation() = 0;
		virtual float GetMouseX_Implementation() = 0;
		virtual float GetMouseY_Implementation() = 0;

	private:

		static Input* Instance;
	};
}