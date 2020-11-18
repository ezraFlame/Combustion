#include <Combustion.h>

class TestLayer : public Combustion::Layer {
public:
	TestLayer() : Layer("Test") {

	}

	void OnUpdate() override {
		//CB_INFO("TestLayer::OnUpdate()");
	}

	void OnEvent(Combustion::Event& event) override {
		CB_INFO("{0}", event);
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