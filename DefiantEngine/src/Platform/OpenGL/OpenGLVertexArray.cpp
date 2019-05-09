#include "depch.h"

#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Defiant {
	void OpenGLVertexArray::createArray() {
		glGenVertexArrays(1, &m_vao);
		Bind();
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		Unbind();
	}

	void OpenGLVertexArray::Bind() {
		glBindVertexArray(m_vao);
	}

	void OpenGLVertexArray::Unbind() {
		glBindVertexArray(0);
	}
}