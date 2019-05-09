#pragma once

namespace Defiant {
	class IndexBuffer {
	public:
		virtual void createBuffer(unsigned int* data, unsigned int count) = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
	};
}