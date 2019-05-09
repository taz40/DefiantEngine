#pragma once

#include "Defiant/Renderer/VertexBuffer.h"

namespace Defiant {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		virtual void createBuffer(float* data, unsigned int count) override;
		virtual void Bind() override;
		virtual void Unbind() override;
	private:
		unsigned int m_vbo;
	};
}