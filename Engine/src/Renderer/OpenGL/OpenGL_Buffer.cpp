#include "aio_pch.h"

#if defined(AIO_API_OPENGL)
#include "OpenGL_Buffer.h"

namespace Alexio
{
	OpenGL_VertexBuffer::OpenGL_VertexBuffer(uint32_t size)
	{
		glCreateBuffers(1, &mID);
		glBindBuffer(GL_ARRAY_BUFFER, mID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	OpenGL_VertexBuffer::OpenGL_VertexBuffer(const void* data, uint32_t size)
	{
		glCreateBuffers(1, &mID);
		glBindBuffer(GL_ARRAY_BUFFER, mID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
	}

	OpenGL_VertexBuffer::~OpenGL_VertexBuffer()
	{
		glDeleteBuffers(1, &mID);
	}

	void OpenGL_VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, mID);
	}

	void OpenGL_VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGL_VertexBuffer::SetData(const void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	/////////////////////////////////////////////////////
	///////////INDEX BUFFER//////////////////////////////
	/////////////////////////////////////////////////////

	OpenGL_IndexBuffer::OpenGL_IndexBuffer(uint32_t* indices, uint32_t count)
	{
		glCreateBuffers(1, &mID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGL_IndexBuffer::~OpenGL_IndexBuffer()
	{
		glDeleteBuffers(1, &mID);
	}

	void OpenGL_IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
	}

	void OpenGL_IndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	
	/////////////////////////////////////////////////////
	///////////VERTEX ARRAY//////////////////////////////
	/////////////////////////////////////////////////////

	OpenGL_VertexArray::OpenGL_VertexArray()
	{
		glCreateVertexArrays(1, &mID);
 		glBindVertexArray(mID);
	}

	OpenGL_VertexArray::~OpenGL_VertexArray()
	{
		glDeleteVertexArrays(1, &mID);
	}

	void OpenGL_VertexArray::Bind() const
	{
		glBindVertexArray(mID);

		for (auto& vertexBuffer : mVertexBuffers)
			vertexBuffer->Bind();

		if (mIndexBuffer != nullptr)
			mIndexBuffer->Bind();
	}

	void OpenGL_VertexArray::Unbind() const
	{
		for (auto& vertexBuffer : mVertexBuffers)
			vertexBuffer->Unbind();
		if (mIndexBuffer != nullptr)
			mIndexBuffer->Unbind();

		glBindVertexArray(0);
	}

	void OpenGL_VertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		mVertexBuffers.push_back(vertexBuffer);
	}

	void OpenGL_VertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(mID);

		indexBuffer->Bind();
		mIndexBuffer = indexBuffer;
	}

	UniformBuffer::UniformBuffer(uint32_t block_size, uint32_t slot)
	{
		glCreateBuffers(1, &mID);
		glNamedBufferData(mID, block_size, nullptr, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, slot, mID);
	}

	UniformBuffer::~UniformBuffer()
	{
		glDeleteBuffers(1, &mID);
	}

	void UniformBuffer::SetData(const void* data, uint32_t data_size)
	{
		glBufferSubData(GL_UNIFORM_BUFFER, 0, data_size, data);
	}

	void UniformBuffer::Bind(uint32_t binding)
	{
		glBindBufferBase(GL_UNIFORM_BUFFER, binding, mID);
	}
}
#endif