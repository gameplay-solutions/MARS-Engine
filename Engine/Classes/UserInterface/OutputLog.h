#pragma once

#include "CoreMinimal.h"
#include "imgui/imgui.h"
#include "Core/Layers/Layer.h"

class OutputLog : Layer
{
	struct ImGuiTextBuffer		Buffer;
	struct ImGuiTextFilter		Filter;
	Array<String>				LogList;
	Array<int32>				LineOffsets;
	bool						bAutoScroll;

public:

	OutputLog(const String& InWindowName);

	void Clear();
	void AddLog(const char* Str);

	virtual void RenderLayerUI(bool* bRender = nullptr) override;

protected:

	void Draw(bool* bOpen);

};
