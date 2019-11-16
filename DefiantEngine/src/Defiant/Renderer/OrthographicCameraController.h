#pragma once

#include "Defiant\Renderer\Camera.h"
#include "Defiant\core\TimeStep.h"

#include "Defiant\Events\ApplicationEvent.h"
#include "Defiant\Events\MouseEvent.h"

namespace Defiant {

	class OrthographicCameraController {
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		virtual void OnUpdate(TimeStep ts) {}
		virtual void OnEvent(Event& e);

		OrthographicCamera& getCamera() { return m_Camera; }
		const OrthographicCamera& getCamera() const { return m_Camera; }
	private:
		bool OnWindowResized(WindowResizeEvent& e);
	protected:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		float m_CameraRotation = 0;
		glm::vec3 m_CameraPosition = { 0, 0, 0 };
	};

}