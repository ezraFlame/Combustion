#include "cbpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Combustion {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}