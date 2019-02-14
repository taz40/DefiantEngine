#include <Defiant.h>

class Sandbox : public Defiant::Application {
public:
	Sandbox() {
		
	}

	~Sandbox() {
		
	}
};


Defiant::Application* Defiant::CreateApplication() {
	return new Sandbox();
}