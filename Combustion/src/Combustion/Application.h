#pragma once

#include "Core.h"

#include "Window.h"
#include "Combustion/LayerStack.h"
#include "Combustion/Events/Event.h"
#include "Combustion/Events/ApplicationEvent.h"]
#include "Combustion/ImGui/ImGuiLayer.h"
#include "imgui.h"

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
		ImGuiContext* GetImGuiContext() { return m_ImGuiContext; }
		void SetImGuiContext(ImGuiContext* context) { m_ImGuiContext = context; }

	private:
		bool OnWindowClose(WindowClosedEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;

		LayerStack m_LayerStack;

		static Application* s_Instance;
		 ImGuiContext* m_ImGuiContext;
	};

	//to be defined in CLIENT
	Application* CreateApplication();
}