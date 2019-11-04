#pragma once

#include "CoreMinimal.h"

inline namespace MARS {
inline namespace DataTypes
{
	template<typename ElementType>
	class MStack
	{
	public:

		MStack();
		~MStack();

		void PushElement(ElementType* InElementType);
		void PushOverlay(ElementType* InElementOverlayType);
		void PopElement(ElementType* InElementType);
		void PopOverlay(ElementType* InElementOverlayType);

		typename std::vector<ElementType*>::iterator begin() { return ElementTypes.begin(); }
		typename std::vector<ElementType*>::iterator end() { return ElementTypes.end(); }

	private:

		std::vector<ElementType*> ElementTypes;
		uint32 ElementTypeInsertIndex;
	};

	template<typename ElementType>
	MStack<ElementType>::MStack()
	{
		ElementTypeInsertIndex = 0;
	}

	template<typename ElementType>
	MStack<ElementType>::~MStack()
	{
		for (auto* It : ElementTypes)
		{
			delete It;
		}
	}

	template<typename ElementType>
	void MStack<ElementType>::PopOverlay(ElementType* InElementOverlayType)
	{
		auto It = std::find(ElementTypes.begin(), ElementTypes.end(), InElementOverlayType);
		if (It != ElementTypes.end())
		{
			ElementTypes.erase(It);
		}
	}

	template<typename ElementType>
	void MStack<ElementType>::PopElement(ElementType* InElementType)
	{
		auto It = std::find(ElementTypes.begin(), ElementTypes.end(), InElementType);
		if (It != ElementTypes.end())
		{
			ElementTypes.erase(It);
			ElementTypeInsertIndex--;
		}
	}

	template<typename ElementType>
	void MStack<ElementType>::PushElement(ElementType* InElementType)
	{
		ElementTypes.emplace(ElementTypes.begin() + ElementTypeInsertIndex, InElementType);
		ElementTypeInsertIndex++;
	}

	template<typename ElementType>
	void MStack<ElementType>::PushOverlay(ElementType* InElementOverlayType)
	{
		ElementTypes.emplace_back(InElementOverlayType);
	}
}}