#include <Combustion.h>
#include "imgui/imgui.h"

class TestLayer : public Combustion::Layer {
public:
	TestLayer() : Layer("Test") {
	}

	void OnUpdate() override {
		//CB_INFO("TestLayer::OnUpdate()");

		if (Combustion::Input::IsKeyPressed(CB_KEY_TAB)) {
			CB_INFO("Tab key is pressed!");
		}
	}

	void OnEvent(Combustion::Event& event) override {
		//CB_TRACE("{0}", event);
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Test");
		ImGui::Text("Hello from Combustion!");
		ImGui::End();
	}
};

class Sandbox : public Combustion::Application {
public:
	Sandbox() {
		PushLayer(new TestLayer());
	}

	~Sandbox() {

	}
};

Combustion::Application* Combustion::CreateApplication() {
	return new Sandbox();
}