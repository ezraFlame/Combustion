#pragma once

#ifdef CB_PLATFORM_WINDOWS

extern Combustion::Application* Combustion::CreateApplication();

int main(int argc, char** argv) {
	Combustion::Log::Init();
	CB_CORE_INFO("Initialized Logs!");
	int a = 5;
	CB_INFO("Hello! Here's the thing you asked for: {0}", a);

	printf("Starting Combustion!!");
	auto app = Combustion::CreateApplication();
	app->Run();
	delete app;
}

#endif