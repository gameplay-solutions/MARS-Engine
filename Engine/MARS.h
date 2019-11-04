#if 1 // this is here until I rework the EngineCore header

extern MARS::Application* MARS::CreateApplication();

int main(int argc, char** argv)
{
	if (argc > 1)
	{
		/** @TODO(Chrisr): Handle command args */
		argv[argc];
	}

	auto* App = MARS::CreateApplication();
	App->InitMARS();
	delete App;

	return 0;
}

#else
#error Unsupported platform, MARS unable to compile!
#endif // PLATFORMS