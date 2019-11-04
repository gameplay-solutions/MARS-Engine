#include "UserInterface/OutputLog.h"

void OutputLog::Clear()
{
	Buffer.clear();
	LineOffsets.clear();
	LineOffsets.push_back(0);
}

void OutputLog::AddLog(const char* Str)
{
	int32 OldSize = Buffer.size();
	for (int32 NewSize = Buffer.size(); OldSize < NewSize; OldSize++)
	{
		if (Buffer[OldSize] == '\n')
		{
			LineOffsets.push_back(OldSize + 1);
		}
	}
}

void OutputLog::Draw(const char* Title, bool* bOpen = nullptr)
{
	if (!ImGui::Begin(Title, bOpen))
	{
		ImGui::End();
		return;
	}

	if (ImGui::BeginPopup("Options"))
	{
		ImGui::Checkbox("Auto-Scroll", &bAutoScroll);
		ImGui::EndPopup();
	}

	if (ImGui::Button("Options")) { ImGui::OpenPopup("Options"); }
	ImGui::SameLine();
	bool bClear = ImGui::Button("Clear");
	ImGui::SameLine();
	bool bCopy = ImGui::Button("Copy");
	ImGui::SameLine();
	Filter.Draw("Filter", -100.0f);

	ImGui::Separator();
	ImGui::BeginChild("Scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

	if (bClear)		{ Clear(); }
	if (bCopy)		{ ImGui::LogToClipboard(); }

	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
	const CHAR* BufferStart = Buffer.begin();
	const CHAR* BufferEnd = Buffer.end();
	if (Filter.IsActive())
	{
		for (int32 LineNumber = 0; LineNumber < LineOffsets.Num(); LineNumber++)
		{
			const CHAR* LineStart = BufferStart + LineOffsets[LineNumber];
			const CHAR* LineEnd = (LineNumber + 1 < LineOffsets.Num()) ? (BufferStart + LineOffsets[LineNumber + 1] - 1) : BufferEnd;
			if (Filter.PassFilter(LineStart, LineEnd)) { ImGui::TextUnformatted(LineStart, LineEnd); }
		}
	}
	else
	{
		ImGuiListClipper _Clipper;
		_Clipper.Begin(LineOffsets.Num());
		while (_Clipper.Step())
		{
			for (int32 LineNumber = _Clipper.DisplayStart; LineNumber < _Clipper.DisplayEnd; LineNumber++)
			{
				const CHAR* LineStart = BufferStart + LineOffsets[LineNumber];
				const CHAR* LineEnd = (LineNumber + 1 < LineOffsets.Num()) ? (BufferStart + LineOffsets[LineNumber + 1] - 1) : BufferEnd;
				ImGui::TextUnformatted(LineStart, LineEnd);
			}
		}
		_Clipper.End();
	}

	ImGui::PopStyleVar();
	if (bAutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) { ImGui::SetScrollHereY(1.0f); }
	ImGui::EndChild();
	ImGui::End();
}
