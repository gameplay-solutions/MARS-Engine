#pragma once

#include "CoreMinimal.h"

inline namespace MARS
{
	struct Element
	{
		// empty struct
	};
	
	struct HeapAllocator
	{
		class ForElemType
		{
		public:
	
			ForElemType()
				: Data(nullptr)
			{ }

			FORCEINLINE void MoveToEmpty(ForElemType& Other)
			{
				Check(this!=&Other)

				if (Data)
				{
					
				}
			}

		private:

			Element* Data;
		};
	};
}