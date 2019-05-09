#pragma once

#include "Defiant/Renderer/VertexArray.h"

namespace Defiant {
	class OpenGLVertexArray : public VertexArray {
	public:
		virtual void createArray() override;
		virtual void Bind() override;
		virtual void Unbind() override;
	private:
		unsigned int m_vao;
	};
}