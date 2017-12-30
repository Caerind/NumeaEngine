#include "VertexBuffer.hpp"

namespace nu
{

VertexBuffer::VertexBuffer()
	: mVertexArray(nullptr)
	, mVertexStruct(VertexStruct_Count)
	, mIndex(0)
	, mVertices(0)
	, mStride(0)
{
	glCheck(glGenBuffers(1, &mIndex));
}

VertexBuffer::VertexBuffer(VertexStruct vertexStruct)
	: mVertexArray(nullptr)
	, mVertexStruct(vertexStruct)
	, mIndex(0)
	, mVertices(0)
	, mStride(0)
{
	glCheck(glGenBuffers(1, &mIndex));
	setStruct(vertexStruct);
}

VertexBuffer::~VertexBuffer()
{
	glCheck(glDeleteBuffers(1, &mIndex));
}

void VertexBuffer::setStruct(VertexStruct vertexStruct)
{
	mVertexArray = VertexArray::get(vertexStruct);
	mVertexStruct = vertexStruct; 
}

void VertexBuffer::bind()
{
	if (mVertexArray != nullptr)
	{
		mVertexArray->bind();
	}
	glCheck(glBindBuffer(GL_ARRAY_BUFFER, mIndex));
}

U32 VertexBuffer::getVertices() const
{
	return mVertices;
}

U32 VertexBuffer::getStride() const
{
	return mStride;
}

U32 VertexBuffer::getSize() const
{
	return mVertices * mStride;
}

bool VertexBuffer::isValid() const
{
	return glIsBuffer(mIndex) == GL_TRUE && mVertexArray != nullptr;
}

U32 VertexBuffer::getId() const
{
	return mIndex;
}

VertexStruct VertexBuffer::getStruct() const
{
	return mVertexStruct;
}

} // namespace nu