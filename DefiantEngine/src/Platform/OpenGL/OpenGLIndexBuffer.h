#pragma once

#include "Defiant/Renderer/IndexBuffer.h"

namespace Defiant {
	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		virtual void createBuffer(unsigned int* data, unsigned int count) override;
		virtual void Bind() override;
		virtual void Unbind() override;
	private:
		unsigned int m_ibo;
	};
}