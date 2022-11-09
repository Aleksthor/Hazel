#include "hzpch.h"
#include "OpenGLBuffer.h"
#include <glad/glad.h>


/*************************************************************************************************************/
//                                      VERTEX BUFFER                                                        //
/*************************************************************************************************************/

Hazel::OpenGLVertexBuffer::OpenGLVertexBuffer(float* verteces, uint32_t size)
{
	
	glCreateBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, verteces, GL_STATIC_DRAW);

}

Hazel::OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void Hazel::OpenGLVertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void Hazel::OpenGLVertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}




/*************************************************************************************************************/
//                                         INDEX BUFFER                                                      //
/*************************************************************************************************************/

Hazel::OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indeces, uint32_t count)
	: m_Count(count)
{
	glCreateBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indeces, GL_STATIC_DRAW);
}

Hazel::OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void Hazel::OpenGLIndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void Hazel::OpenGLIndexBuffer::UnBind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
