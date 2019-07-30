#include "depch.h"

#include "VertexArray.h"
#include "Defiant/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Defiant {
	VertexArray* VertexArray::Create() {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None: DE_CORE_ASSERT(false, "Render API None is not supported");  return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}

		DE_CORE_ASSERT(false, "unknown renderer api");
		return nullptr;
	}
}