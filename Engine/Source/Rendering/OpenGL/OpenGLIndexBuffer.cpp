#include "Rendering/OpenGL/OpenGLIndexBuffer.h"
#include "glad/glad.h"

inline namespace MARS
{

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32* Indices, uint32 Size)
		: Count(Size)
	{
		glCreateBuffers(1, &RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, Count * sizeof(uint32), Indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &RendererID);
	}

	void OpenGLIndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RendererID);
	}

	void OpenGLIndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	uint32 OpenGLIndexBuffer::GetCount() const
	{
		return Count;
	}

}