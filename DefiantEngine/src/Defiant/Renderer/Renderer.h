#pragma once

#include <glm/glm.hpp>

namespace Defiant {
	class Renderer {
	public:

		virtual void clear() = 0;
		virtual void setClearColor(glm::vec4 clearColor) = 0;
		virtual glm::vec4 getClearColor() = 0;
	};
}