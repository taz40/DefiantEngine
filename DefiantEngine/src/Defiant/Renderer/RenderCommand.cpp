#include "depch.h"

#include "RenderCommand.h"
#include "platform/OpenGL/OpenGLRendererAPI.h"

namespace Defiant {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}