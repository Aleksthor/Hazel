#pragma once

#ifdef HZ_PLATFORM_WINDOWS




extern Hazel::Application* Hazel::CreateApplication();


// main function of the project
int main(int argc, char** argv)
{
	Hazel::Log::Init();

	auto app = Hazel::CreateApplication();
	app->Run();

	delete app;

	return 0;
}

#endif