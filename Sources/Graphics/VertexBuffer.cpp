#include "VertexBuffer.hpp"

#include "Renderer.hpp"

namespace nu
{

VertexBuffer::VertexBuffer()
	: mArray()
	, mVertexStruct(VertexStruct_Count)
	, mIndex(0)
	, mVertices(0)
	, mStride(0)
{
	glCheck(glGenBuffers(1, &mIndex));
}

VertexBuffer::~VertexBuffer()
{
	glCheck(glDeleteBuffers(1, &mIndex));
}

void VertexBuffer::bind()
{
	mArray.bind();
	glCheck(glBindBuffer(GL_ARRAY_BUFFER, mIndex));
}

void VertexBuffer::draw()
{
	Renderer::instance().drawArrays(Primitive::Triangles, mVertices);
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
	return glIsBuffer(mIndex) == GL_TRUE && mVertexStruct != VertexStruct_Count;
}

U32 VertexBuffer::getOpenGLId() const
{
	return mIndex;
}

VertexStruct VertexBuffer::getStruct() const
{
	return mVertexStruct;
}

} // namespace nu