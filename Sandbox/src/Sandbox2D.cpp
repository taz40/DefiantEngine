#include "Sandbox2D.h"
#include "imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>
#include <chrono>

template<typename Fn>
class Timer {
public:
	Timer(const char* name, Fn&& func) 
	: m_Name(name), m_Stopped(false), m_Func(func){
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer() {
		if (!m_Stopped)
			Stop();
	}

	void Stop() {
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		m_Stopped = true;

		float duration = (end - start) * 0.001f;

		m_Func({ m_Name, duration });
	}
private:
	const char* m_Name;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;
	Fn m_Func;
};

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {

}

void Sandbox2D::OnAttach() {
	m_Texture = Defiant::Texture2D::Create("assets/textures/checkerboard.png");
	m_TextureCherno = Defiant::Texture2D::Create("assets/textures/ChernoLogo.png");
}

void Sandbox2D::OnDetach() {

}

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult result) {m_ProfileResults.push_back(result); })

void Sandbox2D::OnUpdate(Defiant::TimeStep ts) {
	PROFILE_SCOPE("Sandbox2D::OnUpdate");
	//Update
	{
		PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}
	//Render
	{
		PROFILE_SCOPE("Renderer Prep");
		Defiant::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		Defiant::RenderCommand::Clear();
	}

	{
		PROFILE_SCOPE("Renderer Draw");
		Defiant::Renderer2D::BeginScene(m_CameraController.getCamera());

		Defiant::Renderer2D::DrawQuad({ -1, 0 }, { .8f, .8f }, { 1, 0, 0, 1 });
		Defiant::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, m_SquareColor);
		Defiant::Renderer2D::DrawQuad({ 0.2f, 0.5f, -0.1f }, { 10.0f, 10.0f }, m_Texture, { 10, 10 });
		Defiant::Renderer2D::DrawQuad({ 0, 0, 0.1f}, { 1, 1 }, m_TextureCherno);

		Defiant::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	if (ImGui::CollapsingHeader("Profiling")) {
		for (auto& result : m_ProfileResults) {
			char label[50];
			strcpy(label, "%.3fms  ");
			strcat(label, result.Name);
			ImGui::Text(label, result.Time);
		}
	}
	m_ProfileResults.clear();

	ImGui::End();
}

void Sandbox2D::OnEvent(Defiant::Event& e) {
	m_CameraController.OnEvent(e);
}