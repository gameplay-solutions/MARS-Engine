#pragma once

#include "Core/EngineCore.h"

namespace MARS
{
	class EXPORT_TYPE Layer
	{
	public:

		Layer(const String& Name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& InEvent) {}

		inline const String& GetName() const { return DebugName; }

	protected:

		String DebugName;
	};
}