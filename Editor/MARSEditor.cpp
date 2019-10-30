#include <MARSCore.h>
#include "imgui\imgui.h"

class DetailsPanel : public Layer
{
public:

	DetailsPanel()
	{
	}

	virtual void RenderLayerUI() override
	{
 		ImGui::Begin("Editor Settings");
 		ImGui::Text("FPS %.3f ms/frame (%.1f FPS)", 1000.f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
 		ImGui::End();
	}
};

class MARSEditor : public MARS::Application
{
public:
	MARSEditor()
	{
		PushLayer(new DetailsPanel());
	}
	~MARSEditor(){}
};

MARS::Application* MARS::CreateApplication()
{
	return new MARSEditor();
}