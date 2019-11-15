#include "Sandbox2D.h"
#include "imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {

}

void Sandbox2D::OnAttach() {
	m_Texture = Defiant::Texture2D::Create("assets/textures/checkerboard.png");
}

void Sandbox2D::OnDetach() {

}

void Sandbox2D::OnUpdate(Defiant::TimeStep ts) {
	//Update
	m_CameraController.OnUpdate(ts);

	//Render
	Defiant::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
	Defiant::RenderCommand::Clear();

	Defiant::Renderer2D::BeginScene(m_CameraController.getCamera());
	
	Defiant::Renderer2D::DrawQuad({ -1, 0 }, { .8f, .8f }, {1, 0, 0, 1});
	Defiant::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, m_SquareColor);
	Defiant::Renderer2D::DrawQuad({ 0.2f, 0.5f, -0.1f }, { 10.0f, 10.0f }, m_Texture, { 10, 10 });

	Defiant::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Defiant::Event& e) {
	m_CameraController.OnEvent(e);
}