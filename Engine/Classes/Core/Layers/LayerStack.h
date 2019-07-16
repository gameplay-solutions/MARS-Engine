#pragma once

#include "Core/EngineCore.h"
#include "Core/Layers/Layer.h"

namespace MARS
{
	class EXPORT_TYPE LayerStack
	{
	public:

		LayerStack();
		~LayerStack();

		void PushLayer(Layer* InLayer);
		void PushOverlay(Layer* InOverlay);
		void PopLayer(Layer* InLayer);
		void PopOverlay(Layer* InOverlay);

		std::vector<Layer*>::iterator begin() { return Layers.begin(); }
		std::vector<Layer*>::iterator end() { return Layers.end(); }

	private:

		std::vector<Layer*> Layers;
		std::vector<Layer*>::iterator LayerInsert;
	};
}