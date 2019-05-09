#include "depch.h"

#include "OpenGLVertexBuffer.h"

#include <glad/glad.h>

namespace Defiant {
	void OpenGLVertexBuffer::createBuffer(float* data, unsigned int count) {
		glGenBuffers(1, &m_vbo);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, sizeof(data) * count, data, GL_STATIC_DRAW);
		Unbind();
	}

	void OpenGLVertexBuffer::Bind() {
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	}

	void OpenGLVertexBuffer::Unbind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}