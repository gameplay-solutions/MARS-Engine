#include <MARSCore.h>
#include "Input\InputHandler.h"
#include "Input\Keys.h"

class TestLayer : public MARS::Layer
{
public:

	TestLayer() : Layer("Test") { }

	void OnUpdate() override
	{
		if (MARS::Input::IsKeyPressed(Keys::A))
		{
			std::cout << "Key Pressed \n";
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
	}
	~MARSEditor(){}
};

MARS::Application* MARS::CreateApplication()
{
	return new MARSEditor();
}