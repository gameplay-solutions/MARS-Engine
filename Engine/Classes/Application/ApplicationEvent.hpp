#pragma once
#include "Core/Event.h"
#include "Core/EngineCore.h"

namespace MARS
{
	class __declspec(dllexport) OnWindowResize : public Event
	{
	public: 
		
		/** @todo(Chrisr): We need to create a MARS Vector class so we can have vectors of types other than floats */
		/*OnWindowResize(glm::vec2 NewSize)
			: Size(NewSize)
		{}*/

		OnWindowResize(uint32 InWidth, uint32 InHeight)
			: Width(InWidth)
			, Height(InHeight)
		{}

		/** @todo(Chrisr): delete these Getters and replace it with one that returns a MARS Vector */
		FORCEINLINE uint32 GetWidth() const { return Width; }
		FORCEINLINE uint32 GetHeight() const { return Height; }

		IMPLEMENT_INTERFACE_FUNCTIONS(WindowResize)
		SET_CATEGORIES(CategoryApplication)

	private:

		uint32 Width, Height;
	};

	class __declspec(dllexport) OnWindowClose : public Event
	{
	public:

		OnWindowClose() = default;

		IMPLEMENT_INTERFACE_FUNCTIONS(WindowClose)
		SET_CATEGORIES(CategoryApplication)
	};
}