#include "Core/Layers/LayerStack.h"

MARS::LayerStack::LayerStack()
{
	LayerInsert = Layers.begin();
}

MARS::LayerStack::~LayerStack()
{
	for (auto* It : Layers)
	{
		delete It;
	}
}

void MARS::LayerStack::PushLayer(Layer* InLayer)
{
	LayerInsert = Layers.emplace(LayerInsert, InLayer);
}

void MARS::LayerStack::PushOverlay(Layer* InOverlay)
{
	Layers.emplace_back(InOverlay);
}

void MARS::LayerStack::PopLayer(Layer* InLayer)
{
	auto It = std::find(Layers.begin(), Layers.end(), InLayer);
	if (It != Layers.end())
	{
		Layers.erase(It);
		LayerInsert--;
	}
}

void MARS::LayerStack::PopOverlay(Layer* InOverlay)
{
	auto It = std::find(Layers.begin(), Layers.end(), InOverlay);
	if (It != Layers.end())
	{
		Layers.erase(It);
	}
}

