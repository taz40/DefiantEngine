#pragma once

#include "RendererAPI.h"

namespace Defiant {
	class RenderCommand {
	public:
		static inline void Init() { s_RendererAPI->Init(); }
		static inline void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { s_RendererAPI->SetViewport(x, y, width, height); }
		static inline void DrawIndexed(const Ref<VertexArray>& vertexArray) { s_RendererAPI->DrawIndexed(vertexArray); }
		static inline void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); }
		static inline void Clear() { s_RendererAPI->Clear(); }
	private:
		static RendererAPI* s_RendererAPI;
	};
}