#pragma once

#include "Defiant/Renderer/Renderer.h"

namespace Defiant{
	class OpenGLRenderer : public Renderer {
	public:
		OpenGLRenderer();

		virtual void clear() override;
		virtual void setClearColor(glm::vec4 clearColor) override;
		virtual glm::vec4 getClearColor() override;
	private:
		glm::vec4 m_ClearColor;
	};
}