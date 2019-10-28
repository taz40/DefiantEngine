#include "depch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Defiant {
	Ref<Texture2D> Texture2D::Create(const std::string& path) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None: DE_CORE_ASSERT(false, "Render API None is not supported");  return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
		}

		DE_CORE_ASSERT(false, "unknown renderer api");
		return nullptr;
	}
}