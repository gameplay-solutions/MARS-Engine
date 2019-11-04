#include "Rendering/OpenGL/OpenGLVertexBuffer.h"
#include "glad/glad.h"

using namespace MARS;

void OpenGLVertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void OpenGLVertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

OpenGLVertexBuffer::OpenGLVertexBuffer(float* Verts, uint32 Size)
{
	glCreateBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, Size, Verts, GL_STATIC_DRAW);
}

MARS::OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void MARS::OpenGLVertexBuffer::SetLayout(const BufferLayout& Layout)
{
	m_Layout = Layout;
}

const MARS::BufferLayout& MARS::OpenGLVertexBuffer::GetLayout() const
{
	return m_Layout;
}
