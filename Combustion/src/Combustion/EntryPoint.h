#pragma once

#ifdef CB_PLATFORM_WINDOWS

extern Combustion::Application* Combustion::CreateApplication();

int main(int argc, char** argv) {
	printf("Starting Combustion!!");
	auto app = Combustion::CreateApplication();
	app->Run();
	delete app;
}

#endif