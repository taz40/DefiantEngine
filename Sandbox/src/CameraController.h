#pragma once

#include "Defiant\Renderer\Camera.h"
#include "Defiant\core\TimeStep.h"

#include "Defiant\Events\ApplicationEvent.h"
#include "Defiant\Events\MouseEvent.h"
#include "Defiant\Renderer\OrthographicCameraController.h"

class CameraController : public Defiant::OrthographicCameraController {
public:
	CameraController(float aspectRatio, bool rotation = false);

	virtual void OnUpdate(Defiant::TimeStep ts);
	virtual void OnEvent(Defiant::Event& e);
private:
	bool OnMouseScrolled(Defiant::MouseScrolledEvent& e);
private:
	float m_CameraTranslationSpeed = 2.0f, m_CameraRotationSpeed = 180.0f;
};