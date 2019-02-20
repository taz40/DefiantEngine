#include <Defiant.h>

class ExampleLayer : public Defiant::Layer {
public:
	ExampleLayer()
		: Layer("Example"){
	}

	void OnUpdate() override {

	}

	void OnEvent(Defiant::Event& event) override {
		//DE_TRACE("{0}", event)
	}
};

class Sandbox : public Defiant::Application {
public:
	Sandbox() {
		DE_TRACE("Created Sandbox App");
		PushLayer(new ExampleLayer());
		PushOverlay(new Defiant::ImGuiLayer());
	}

	~Sandbox() {
		
	}
};


Defiant::Application* Defiant::CreateApplication() {
	return new Sandbox();
}