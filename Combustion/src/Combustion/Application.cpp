#include "Application.h"

#include "Combustion/Events/ApplicationEvent.h"
#include "Combustion/Log.h"

namespace Combustion {
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run() {
		WindowResizedEvent e(1280, 720);
		CB_INFO(e.ToString());

		while (true);
	}
}
