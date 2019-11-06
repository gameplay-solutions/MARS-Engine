#include "Core/Layers/Layer.h"

using namespace MARS;

Layer::Layer(const String& Name /*= "Layer"*/)
{
	DebugName = Name;
	bDrawUserInterface = false;
}

Layer::~Layer()
{

}

