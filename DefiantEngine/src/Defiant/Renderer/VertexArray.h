#pragma once

namespace Defiant {
	class VertexArray {
	public:
		virtual void createArray() = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
	};
}