#pragma once

#include "Core.h"

#include "Window.h"
#include "Combustion/LayerStack.h"

#include "Combustion/Events/Event.h"
#include "Combustion/Events/ApplicationEvent.h"

#include "ImGui/ImGuiLayer.h"

#include "Combustion/Core/Timestep.h"

#include "Combustion/Renderer/OrthographicCamera.h"

namespace Combustion {
	class CB_API Application {
	public:
		Application();
		virtual ~Application();
		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		static inline Application& Get() { return *s_Instance; }

		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowClosedEvent& e);
		
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		static Application* s_Instance;

		float m_LastFrameTime = 0.0f;
	};

	//to be defined in CLIENT
	Application* CreateApplication();
}