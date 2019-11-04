#pragma once

#include "CoreMinimal.h"
#include "imgui/imgui.h"

class OutputLog
{
	struct ImGuiTextBuffer		Buffer;
	struct ImGuiTextFilter		Filter;
	Array<String>				LogList;
	Array<int32>				LineOffsets;
	bool						bAutoScroll;

public:

	void Clear();
	void AddLog(const char* Str);
	void Draw(const char* Title, bool* bOpen);

};
