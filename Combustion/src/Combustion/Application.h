#pragma once

#include "Core.h"

#include "Window.h"
#include "Combustion/LayerStack.h"
#include "Combustion/Events/Event.h"
#include "Combustion/Events/ApplicationEvent.h"

namespace Combustion {
	class CB_API Application {
	public:
		Application();
		virtual ~Application();
		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
	private:
		bool OnWindowClose(WindowClosedEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		LayerStack m_LayerStack;
	};

	//to be defined in CLIENT
	Application* CreateApplication();
}