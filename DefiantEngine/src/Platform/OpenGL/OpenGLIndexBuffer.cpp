#include "depch.h"

#include "OpenGLIndexBuffer.h"

#include <glad/glad.h>

namespace Defiant {
	void OpenGLIndexBuffer::createBuffer(unsigned int* data, unsigned int count) {
		glGenBuffers(1, &m_ibo);
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(data) * count, data, GL_STATIC_DRAW);
		Unbind();
	}

	void OpenGLIndexBuffer::Bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	}

	void OpenGLIndexBuffer::Unbind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}