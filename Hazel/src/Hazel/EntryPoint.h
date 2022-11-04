#pragma once

#ifdef HZ_PLATFORM_WINDOWS



extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
	Hazel::Log::Init();

	HZ_CORE_WARN("Initilizing . .");
	HZ_INFO("Initialized");

	auto app = Hazel::CreateApplication();
	app->Run();

	delete app;

	return 0;
}

#endif