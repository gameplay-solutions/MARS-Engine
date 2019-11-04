#include "Rendering/BufferLayout.h"

void MARS::BufferLayout::CalcOffsetsAndStride()
{
	Stride = 0;
	for (auto& _Element : Elements)
	{
		_Element.Offset = Stride;
		Stride += _Element.Size;
	}
}
