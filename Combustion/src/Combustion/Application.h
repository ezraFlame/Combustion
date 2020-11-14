#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace Combustion {
	class CB_API Application {
	public:
		Application();
		virtual ~Application();
		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	//to be defined in CLIENT
	Application* CreateApplication();
}