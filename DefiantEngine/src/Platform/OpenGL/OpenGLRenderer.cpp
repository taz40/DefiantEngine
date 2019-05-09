#include "depch.h"

#include "OpenGLRenderer.h"

#include <glad/glad.h>

namespace Defiant {

	OpenGLRenderer::OpenGLRenderer() {
		setClearColor(glm::vec4(1.0, 0.0, 1.0, 1.0));
	}

	void OpenGLRenderer::clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderer::setClearColor(glm::vec4 clearColor) {
		m_ClearColor = clearColor;
		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	}

	glm::vec4 OpenGLRenderer::getClearColor() {
		return m_ClearColor;
	}
}