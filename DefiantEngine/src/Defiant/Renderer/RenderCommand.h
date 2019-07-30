#pragma once

#include "RendererAPI.h"

namespace Defiant {
	class RenderCommand {
	public:
		static inline void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) { s_RendererAPI->DrawIndexed(vertexArray); }
		static inline void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); }
		static inline void Clear() { s_RendererAPI->Clear(); }
	private:
		static RendererAPI* s_RendererAPI;
	};
}