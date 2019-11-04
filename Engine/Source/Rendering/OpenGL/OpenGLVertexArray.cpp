#include "Rendering/OpenGL/OpenGLVertexArray.h"
#include "glad/glad.h"
#include "Rendering/BufferLayout.h"

OpenGLVertexArray::OpenGLVertexArray()
{
	glCreateVertexArrays(1, &m_RendererID);
}

OpenGLVertexArray::~OpenGLVertexArray()
{

}

void OpenGLVertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void OpenGLVertexArray::Unbind() const
{
	glBindVertexArray(0);
}

static GLenum Convert(ShaderDataType In)
{
	switch (In)
	{
		case MARS::ShaderDataType::Float:return GL_FLOAT;
		case MARS::ShaderDataType::Float2:return GL_FLOAT;
		case MARS::ShaderDataType::Float3:return GL_FLOAT;
		case MARS::ShaderDataType::Float4:return GL_FLOAT;
		case MARS::ShaderDataType::Mat3:return GL_FLOAT;
		case MARS::ShaderDataType::Mat4:return GL_FLOAT;
		case MARS::ShaderDataType::Int:return GL_INT;
		case MARS::ShaderDataType::Int2:return GL_INT;
		case MARS::ShaderDataType::Int3:return GL_INT;
		case MARS::ShaderDataType::Int4:return GL_INT;
	}
	return 0;
}

void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& InBuffer)
{
	Assertf(InBuffer->GetLayout().GetElements().size(), "Vertex Buffer is empty");
	
	Bind();
	InBuffer->Bind();

	uint32 i = 0;
	for (const auto& Element : InBuffer->GetLayout())
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, Element.GetComponentCount(), Convert(Element.Type), Element.bNormalized ? GL_TRUE : GL_FALSE,
							  InBuffer->GetLayout().GetStride(), (const void*)Element.Offset);
		i++;
	}
	
	m_VertexBuffers.push_back(InBuffer);
}

void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& InBuffer)
{
	Bind();
	InBuffer->Bind();
	m_IndexBuffer = InBuffer;
}

Array<std::shared_ptr<MARS::VertexBuffer>> OpenGLVertexArray::GetVertexBuffer() const
{
	return m_VertexBuffers;
}

std::shared_ptr<MARS::IndexBuffer> OpenGLVertexArray::GetIndexBuffer() const
{
	return m_IndexBuffer;
}
