#include "cbpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Combustion {
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type)
		{
		case Combustion::ShaderDataType::None:		return GL_FLOAT;
		case Combustion::ShaderDataType::Float:		return GL_FLOAT;
		case Combustion::ShaderDataType::Float2:	return GL_FLOAT;
		case Combustion::ShaderDataType::Float3:	return GL_FLOAT;
		case Combustion::ShaderDataType::Float4:	return GL_FLOAT;
		case Combustion::ShaderDataType::Mat3:		return GL_FLOAT;
		case Combustion::ShaderDataType::Mat4:		return GL_FLOAT;
		case Combustion::ShaderDataType::Int:		return GL_INT;
		case Combustion::ShaderDataType::Int2:		return GL_INT;
		case Combustion::ShaderDataType::Int3:		return GL_INT;
		case Combustion::ShaderDataType::Int4:		return GL_INT;
		case Combustion::ShaderDataType::Bool:		return GL_INT;
		}

		CB_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return GL_NONE;
	}

	OpenGLVertexArray::OpenGLVertexArray() {
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const {
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const {
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
		CB_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!");
		
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();


		uint32_t index = 0;
		for (const auto& element : vertexBuffer->GetLayout()) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, vertexBuffer->GetLayout().GetStride(), (const void*)element.Offset);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
		glBindVertexArray(m_RendererID);

		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}