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
		Defiant::Application& app = Defiant::Application::Get();
		ImGui::Begin("Clear Color");
		glm::vec4 col = app.renderer->getClearColor();
		float* rgba = new float[3]{ col[0], col[1], col[2] };
		if (ImGui::ColorPicker3("Clear Color", rgba)) {
			app.renderer->setClearColor(glm::vec4(rgba[0], rgba[1], rgba[2], 1.0));
		}
		ImGui::End();

	}

	void OnEvent(Defiant::Event& event) override {

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