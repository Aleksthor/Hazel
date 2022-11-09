#include "hzpch.h"
#include "RenderCommands.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Hazel
{
	RendererAPI* RenderCommands::s_RendererAPI = new OpenGLRendererAPI;
}