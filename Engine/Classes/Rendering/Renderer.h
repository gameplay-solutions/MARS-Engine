#pragma once

#include "glad/glad.h"
#include "Core/EngineCore.h"

namespace MARS
{
	/** 
	 *	This class maintains a render buffer queue, sorts the buffer, 
	 *	and manages multiple render passes and render buffers 
	 **/
	class FRenderer
	{
	public:

		void Init(GLADloadproc LoadProc);

		void SetRenderSize(uint32 NewWidth, uint32 NewHeight);
		FORCEINLINE glm::vec2 GetRenderSize();
	};
}