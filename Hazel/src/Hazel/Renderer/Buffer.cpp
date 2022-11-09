#include "hzpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Hazel
{
	VertexBuffer* VertexBuffer::Create(float* verteces, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
				return nullptr;
				break;
		case RendererAPI::API::OpenGL:
				return new OpenGLVertexBuffer(verteces, size);
				break;
			default:
				return nullptr;
				break;

		}



	}
	IndexBuffer* IndexBuffer::Create(uint32_t* indeces, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			return nullptr;
			break;
		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indeces, count);
			break;
		default:
			return nullptr;
			break;

		}
	}
}