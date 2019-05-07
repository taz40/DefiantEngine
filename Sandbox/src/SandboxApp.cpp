#include <Defiant.h>

#include "imgui/imgui.h"

class ExampleLayer : public Defiant::Layer {
public:
	ExampleLayer()
		: Layer("Example"){
	}

	void OnUpdate() override {

	}

	void OnImGuiRender() override {
		ImGui::Begin("Test");
		ImGui::Text("Hello, World!");
		ImGui::End();
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
	}

	~Sandbox() {
		
	}
};


Defiant::Application* Defiant::CreateApplication() {
	return new Sandbox();
}