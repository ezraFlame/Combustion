#include <Combustion.h>

class Sandbox : public Combustion::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

Combustion::Application* Combustion::CreateApplication() {
	return new Sandbox();
}