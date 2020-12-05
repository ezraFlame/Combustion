#pragma once

#include "Core.h"

#include "Window.h"
#include "Combustion/LayerStack.h"
#include "Combustion/Events/Event.h"
#include "Combustion/Events/ApplicationEvent.h"
#include "Combustion/ImGui/ImGuiLayer.h"
#include "Combustion/Renderer/Shader.h"

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

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;

		std::unique_ptr<Shader> m_Shader;

		static Application* s_Instance;
	};

	//to be defined in CLIENT
	Application* CreateApplication();
}