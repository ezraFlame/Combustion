#include <Combustion.h>
#include "imgui/imgui.h"

using namespace Combustion;

class TestLayer : public Combustion::Layer {
public:
	TestLayer() : Layer("Test") {
	}

	bool showChild = false;

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