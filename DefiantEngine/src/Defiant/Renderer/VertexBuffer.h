#pragma once

namespace Defiant {
	class VertexBuffer {
	public:
		virtual void createBuffer(float* data, unsigned int count) = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
	};
}