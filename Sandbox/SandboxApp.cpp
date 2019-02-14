#include <Defiant.h>

class Sandbox : public Defiant::Application {
public:
	Sandbox() {
		DE_TRACE("Created Sandbox App");
	}

	~Sandbox() {
		
	}
};


Defiant::Application* Defiant::CreateApplication() {
	return new Sandbox();
}