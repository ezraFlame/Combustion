#include <Combustion.h>

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
};

class Sandbox : public Combustion::Application {
public:
	Sandbox() {
		PushLayer(new TestLayer());
		PushOverlay(new Combustion::ImGuiLayer());
	}

	~Sandbox() {

	}
};

class TestGui : public Combustion::Layer {
public:
	TestGui() : Layer("Gui") {

	}
};

Combustion::Application* Combustion::CreateApplication() {
	return new Sandbox();
}