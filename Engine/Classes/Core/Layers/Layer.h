#pragma once

#include "CoreMinimal.h"

inline namespace MARS
{
	class EXPORT_TYPE Layer
	{
	public:

		Layer(const String& Name = "Layer");
		virtual ~Layer();


		virtual void OnEnd()					{}
		virtual void OnBegin()					{}
		virtual void OnAttach()					{}
		virtual void OnDetach()					{}
		virtual void OnUpdate()					{}
		virtual void RenderLayerUI()			{}
		virtual void OnEvent(Event& InEvent)	{}


		inline const String& GetName() const { return DebugName; }

	protected:

		String DebugName;
	};
}