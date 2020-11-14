#include "cbpch.h"

#include "Application.h"

#include "Combustion/Events/ApplicationEvent.h"
#include "Combustion/Log.h"

namespace Combustion {
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run() {
		while (m_Running) {
			m_Window->OnUpdate();
		}
	}
}
