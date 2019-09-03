#include "depch.h"
#include "Shader.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Defiant {
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None: DE_CORE_ASSERT(false, "Render API None is not supported");  return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		DE_CORE_ASSERT(false, "unknown renderer api");
		return nullptr;
	}
}