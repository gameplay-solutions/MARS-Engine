#include <MARSCore.h>

class TestLayer : public MARS::Layer
{
public:

	TestLayer() : Layer("Test") { }

	void OnUpdate() override
	{
		if (MARS::Input::IsKeyPressed(Keys::A))
		{
			std::cout << "Key Pressed" << std::endl;
		}
	}

	void OnEvent(MARS::Event& InEvent) override
	{
	}
};

class MARSEditor : public MARS::Application
{
public:
	MARSEditor()
	{
		PushLayer(new TestLayer());
		PushOverlay(new MARS::ImGuiLayer());
	}
	~MARSEditor(){}

	
};

MARS::Application* MARS::CreateApplication()
{
	return new MARSEditor();
}