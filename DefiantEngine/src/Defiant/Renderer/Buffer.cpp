#include "depch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Defiant {
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None: DE_CORE_ASSERT(false, "Render API None is not supported");  return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}

		DE_CORE_ASSERT(false, "unknown renderer api");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None: DE_CORE_ASSERT(false, "Render API None is not supported");  return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLIndexBuffer>(indices, count);
		}

		DE_CORE_ASSERT(false, "unknown renderer api");
		return nullptr;
	}
}