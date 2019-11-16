#pragma once

#include "Defiant.h"
#include "CameraController.h"

class Sandbox2D : public Defiant::Layer {
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Defiant::TimeStep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Defiant::Event& e) override;

private:
	CameraController m_CameraController;
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	Defiant::Ref<Defiant::Texture2D> m_Texture;
	Defiant::Ref<Defiant::Texture2D> m_TextureCherno;
	Defiant::Ref<Defiant::SoundClip> m_Sound;

	struct ProfileResult {
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_ProfileResults;

};