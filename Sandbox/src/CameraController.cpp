#include "depch.h"
#include "CameraController.h"

#include "Defiant/Core/Input.h"
#include "Defiant/Core/KeyCodes.h"

CameraController::CameraController(float aspectRatio, bool rotation)
	: OrthographicCameraController(aspectRatio, rotation) {
		
}

void CameraController::OnUpdate(Defiant::TimeStep ts) {
	if (Defiant::Input::IsKeyPressed(DE_KEY_A)) {
		m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
	}
	if (Defiant::Input::IsKeyPressed(DE_KEY_D)) {
		m_CameraPosition.x += m_CameraTranslationSpeed * ts;
	}

	if (Defiant::Input::IsKeyPressed(DE_KEY_W)) {
		m_CameraPosition.y += m_CameraTranslationSpeed * ts;
	}
	if (Defiant::Input::IsKeyPressed(DE_KEY_S)) {
		m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
	}

	if (m_Rotation) {
		if (Defiant::Input::IsKeyPressed(DE_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Defiant::Input::IsKeyPressed(DE_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * ts;
			
		m_Camera.SetRotation(m_CameraRotation);
	}

	m_Camera.SetPosition(m_CameraPosition);

	m_CameraTranslationSpeed = m_ZoomLevel;
}

void CameraController::OnEvent(Defiant::Event& e) {
	OrthographicCameraController::OnEvent(e);
	Defiant::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Defiant::MouseScrolledEvent>(BIND_EVENT_FN(CameraController::OnMouseScrolled));
}

bool CameraController::OnMouseScrolled(Defiant::MouseScrolledEvent& e) {
	m_ZoomLevel -= e.getYOffset() * .25f;
	m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
	m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	return false;
}