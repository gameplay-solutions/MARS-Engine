#include <MARSCore.h>

class TestLayer : public MARS::Layer
{
public:

	TestLayer() : Layer("Test") {}

	void OnUpdate() override
	{
		//Log::Get(LogTemp).Info("{}", GetName());
		//std::cout << GetName() << std::endl;
	}

	void OnEvent(MARS::Event& InEvent) override
	{
		//Log::Get(LogTemp).Info("{}", InEvent.ToString());
		std::cout << InEvent.ToString().c_str() << std::endl;
	}
};

class MARSEditor : public MARS::Application
{
public:
	MARSEditor()
	{
		PushOverlay(new MARS::ImGuiLayer());
	}
	~MARSEditor(){}
};

MARS::Application* MARS::CreateApplication()
{
	return new MARSEditor();
}